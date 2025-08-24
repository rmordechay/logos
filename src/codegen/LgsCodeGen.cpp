#include "codegen/LgsCodeGen.h"
#include "funcs/LgsCoroutine.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "exprs/unary/LgsCast.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/LgsFuncCall.h"
#include "exprs/unary/LgsInstance.h"
#include "exprs/unary/LgsSelection.h"
#include "exprs/unary/LgsVariable.h"
#include "exprs/LgsBinaryExpr.h"
#include "types/LgsEnum.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterator.h"
#include "exprs/unary/LgsPostfixExpr.h"
#include "exprs/unary/LgsPrefixExpr.h"
#include "exprs/unary/LgsVectorExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "funcs/LgsMainFunc.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsDArray.h"
#include "types/LgsInterface.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIfStmt.h"
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

void LgsCodeGen::generate(const LgsAppConfigs& appConfigs, TargetMachine& targetMachine) {
    cg.targetMachine = &targetMachine;
    cg.setupModule(file, appConfigs.debugMode);
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(&file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(&file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(&file)) {
        visitInterface(interfaceFile->interface);
    }
}

void LgsCodeGen::visitMainFile(LgsMainFile* mainFile) {
    for (const auto object : mainFile->objects) {
        visitObject(object);
        for (const auto& [_, method] : object->methods) {
            visitFunc(method);
        }
    }
    for (const auto [_, func] : mainFile->funcs) {
        if (const auto mainFunc = dynamic_cast<LgsMainFunc*>(func)) {
            visitMainFunc(mainFunc);
        } else {
            visitFunc(func);
        }
    }
}

void LgsCodeGen::visitObjFile(const LgsObjectFile* objFile) {
    visitObject(objFile->obj);
    for (const auto& [_, method] : objFile->obj->methods) {
        visitFunc(method);
    }
}

void LgsCodeGen::visitInterfaceFile(const LgsInterfaceFile* interfaceFile) {
    for (const auto& [_, method] : interfaceFile->interface->methods) {
        if (!method->stmtsBlock) continue;
        visitFunc(method);
    }
}

void LgsCodeGen::visitMainFunc(LgsMainFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    // codeGen->callRuntimeInit();
    if (!func->funcType->params.empty()) func->initMainArgs(cg);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    cg.builder.CreateRet(cg.i32(EXIT_SUCCESS));
    stack.exitScope();
}

void LgsCodeGen::visitFunc(LgsFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    if (!cg.lastInstTerminator()) cg.builder.CreateRetVoid();
    stack.exitScope();
}

void LgsCodeGen::visitObject(LgsObject* obj) const {
    if (obj->IRType) return;
    std::vector<Type*> elementTypes;
    elementTypes.reserve(obj->fields.size());
    for (int i = 0; i < obj->fields.size(); ++i) {
        const auto field = obj->fields[i];
        field->position = i;
        Type* fieldType;
        if (field->type->asObject() || field->type->asFuncType()) {
            fieldType = cg.ptrTy();
        } else {
            fieldType = field->type->getIRType(cg);
        }
        elementTypes.push_back(fieldType);
    }
    obj->IRType = StructType::getTypeByName(cg.context, obj->name);
    if (!obj->IRType) {
        obj->IRType = StructType::create(cg.context, elementTypes, obj->name);
    }
    for (const auto& field : obj->fields) {
        field->parentIRType = obj->IRType;
    }
}

void LgsCodeGen::visitInterface(LgsInterface* interface) const {
    if (interface->IRType) return;
    interface->IRType = StructType::getTypeByName(cg.context, interface->name);
    std::vector<Type*> elementTypes;
    for (int i = 0; i < interface->methods.size(); ++i) {
        elementTypes.emplace_back(cg.ptrTy());
    }
    if (!interface->IRType) {
        interface->IRType = StructType::create(cg.context, elementTypes, interface->name);
    }
}

void LgsCodeGen::visitGroup(LgsGroup* group) {
    assert(0);
}

void LgsCodeGen::visitField(LgsField* field) const {
    if (field->parentIRType->isVectorTy()) {
        const auto vec = cg.builder.CreateLoad(field->parentIRType, field->parentIRValue);
        const auto i = cg.isize(field->position);
        field->IRValue = cg.builder.CreateExtractElement(vec, i);
    } else {
        field->IRValue = cg.builder.CreateStructGEP(field->parentIRType, field->parentIRValue, field->position);
    }
}

void LgsCodeGen::visitParam(LgsParam* param) {
    visitExpr(param->expr);
    if (!param->isVariadic) return;
    if (param->vaList) {
        param->IRValue = param->vaList;
        return;
    }
    param->vaList = cg.builder.CreateAlloca(cg.builder.getPtrTy());
    const auto vaStart = Intrinsic::getDeclaration(cg.IRModule, Intrinsic::vastart, {cg.builder.getPtrTy()});
    cg.builder.CreateCall(vaStart, {param->vaList});
    param->IRValue = param->vaList;

}

void LgsCodeGen::visitLoop(LgsForLoop* loopStmt) {
    stack.enterScope(loopStmt);
    loopStmt->setBlocks(cg);
    if (const auto rangeLoop = dynamic_cast<LgsRangeLoop*>(loopStmt)) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = dynamic_cast<LgsForeachLoop*>(loopStmt)) {
        visitForeachLoop(foreachLoop);
    } else if (const auto infiniteLoop = dynamic_cast<LgsInfiniteLoop*>(loopStmt)) {
        visitInfiniteLoop(infiniteLoop);
    } else if (const auto whileLoop = dynamic_cast<LgsWhileLoop*>(loopStmt)) {
        visitWhileLoop(whileLoop);
    } else {
        assert(0);
    }
    visitStmtsBlock(loopStmt->stmtsBlock);
    loopStmt->incAndJumpToCond(cg);
    cg.startBlock(loopStmt->IRExitBlock, currentIRFunc);
    stack.exitScope();
}

void LgsCodeGen::visitRangeLoop(LgsRangeLoop* loop) {
    loop->iPtr = cg.builder.CreateAlloca(cg.i32Ty());
    cg.builder.CreateStore(loopStart(loop), loop->iPtr);
    cg.builder.CreateBr(loop->IRCondBlock);

    // Condition
    cg.startBlock(loop->IRCondBlock, currentIRFunc);
    const auto iValue = loop->loadIndex(cg);
    const auto condition = cg.builder.CreateICmpSLT(iValue, loopEnd(loop));
    visitLoopTerminals(loop, iValue);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock, currentIRFunc);
    loop->loopVars.front()->setIRValue(iValue);
}

void LgsCodeGen::visitForeachLoop(LgsForeachLoop* loop) {
    loop->iPtr = cg.builder.CreateAlloca(cg.i32Ty());
    cg.builder.CreateStore(cg.i32Zero(), loop->iPtr);
    cg.branchAndStartBlock(loop->IRCondBlock, currentIRFunc);
    const auto iterable = loop->iterExpr->type->asIterable();
    if (iterable->asMap()) { // With iterator
        LgsIterator iterator = loop->iterExpr->toIterator();
        iterator.initIterator(cg);
        cg.builder.CreateCondBr(iterator.hasNext(cg), loop->IRBodyBlock, loop->IRExitBlock);
        cg.startBlock(loop->IRBodyBlock, currentIRFunc);
        loop->iterPtr = getIRValue(loop->iterExpr);
        loop->setMapIterVars(cg, iterator);
    } else { // Without iterator
        auto iValue = loop->loadIndex(cg);
        const auto loopEnd = iterable->IRLength(cg, loop->iterExpr);
        if (loopEnd->getType()->isIntegerTy(64)) {
            iValue = cg.builder.CreateSExt(iValue, cg.i64Ty());
        }
        const auto condition = cg.builder.CreateICmpSLT(iValue, loopEnd);
        cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
        cg.startBlock(loop->IRBodyBlock, currentIRFunc);
        loop->iterPtr = getIRValue(loop->iterExpr);
        if (const auto str = iterable->asStr()) {
            loop->setStrIterVars(cg, str);
        } else if (const auto arr = iterable->asDArray()) {
            loop->setArrIterVars(cg, arr);
        } else {
            assert(0);
        }
    }
}

void LgsCodeGen::visitInfiniteLoop(LgsInfiniteLoop* loop) {
    if (!loop->loopVars.empty()) {
        loop->iPtr = cg.builder.CreateAlloca(cg.i32Ty());
        cg.builder.CreateStore(cg.i32Zero(), loop->iPtr);
    }
    cg.branchAndStartBlock(loop->IRBodyBlock, currentIRFunc);
    if (!loop->loopVars.empty()) {
        const auto iValue = loop->loadIndex(cg);
        loop->loopVars.front()->setIRValue(iValue);
    }
}

void LgsCodeGen::visitWhileLoop(LgsWhileLoop* loop) {
    cg.builder.CreateBr(loop->IRCondBlock);
    // Condition
    cg.startBlock(loop->IRCondBlock, currentIRFunc);
    const auto condition = getIRValue(loop->condExpr);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
    // Body
    cg.startBlock(loop->IRBodyBlock, currentIRFunc);
}

void LgsCodeGen::visitLoopTerminals(const LgsRangeLoop* loop, Value* iValue) {
    if (loop->isFirst) {
        loop->isFirst->setIRValue(cg.builder.CreateICmpEQ(iValue, loopStart(loop)));
    }
    if (loop->isLast) {
        const auto decremented = cg.builder.CreateSub(loopEnd(loop), cg.i32(1));
        loop->isLast->setIRValue(cg.builder.CreateICmpEQ(iValue, decremented));
    }
}

void LgsCodeGen::visitStmt(LgsStmt* stmt) {
    if (const auto ifStmt = stmt->asIfStmt()) return visitIfStmt(ifStmt);
    if (const auto pattern = stmt->asPattern()) return visitPatternMatching(pattern);
    if (const auto varDec = stmt->asVarDec()) return visitVarDec(varDec);
    if (const auto loopStmt = stmt->asLoop()) return visitLoop(loopStmt);
    if (const auto coroutine = stmt->asCoroutine()) return visitCoroutine(coroutine);
    if (const auto deferStmt = stmt->asDefer()) return visitDeferStmt(deferStmt);
    if (const auto assignment = stmt->asAssignment()) return visitAssignment(assignment);
    if (const auto funcCall = stmt->asFuncCall()) return visitFuncCall(funcCall);
    if (const auto postfixExpr = stmt->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
    if (const auto selection = stmt->asSelection()) return visitSelection(selection);
    if (const auto returnStmt = stmt->asReturn()) return visitReturnStmt(returnStmt);
    if (const auto breakStmt = stmt->asBreak()) return visitBreakStmt(breakStmt);
    if (stmt->asContinue()) return visitContinueStmt();
    assert(0);
}

void LgsCodeGen::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    for (const auto stmt : stmtsBlock->stmts) {
        visitStmt(stmt);
    }
}

void LgsCodeGen::visitVarDec(LgsVarDec* varDec) {
    const auto IRType = varDec->type->getIRType(cg);
    const auto exprIRValue = getIRValue(varDec->expr);
    if (varDec->shouldAllocate(IRType)) {
        varDec->IRValue = cg.builder.CreateAlloca(IRType, nullptr, varDec->name);
        cg.builder.CreateStore(exprIRValue, getIRValue(varDec));
    } else {
        varDec->IRValue = exprIRValue;
    }
}

void LgsCodeGen::visitAssignment(const LgsAssignment* assignment) {
    Value* results = nullptr;
    switch (assignment->assignmentType) {
    case ASSIGN: assignment->createIRAssignment(cg); return;
    case ASSIGN_ADD: results = assignment->lValue->addIR(cg, assignment->rValue); break;
    case ASSIGN_SUB: results = assignment->lValue->subIR(cg, assignment->rValue); break;
    case ASSIGN_MUL: results = assignment->lValue->mulIR(cg, assignment->rValue); break;
    case ASSIGN_DIV: results = assignment->lValue->divIR(cg, assignment->rValue); break;
    case ASSIGN_MOD: results = assignment->lValue->modIR(cg, assignment->rValue); break;
    case ASSIGN_AND: results = assignment->lValue->bitAndIR(cg, assignment->rValue); break;
    case ASSIGN_OR: results = assignment->lValue->bitOrIR(cg, assignment->rValue); break;
    case ASSIGN_XOR: results = assignment->lValue->bitXorIR(cg, assignment->rValue); break;
    case ASSIGN_LSHIFT: results = assignment->lValue->lshiftIR(cg, assignment->rValue); break;
    case ASSIGN_RSHIFT: results = assignment->lValue->rshiftIR(cg, assignment->rValue); break;
    }
    assert(results);
    cg.builder.CreateStore(results, getIRValue(assignment->lValue));
}

void LgsCodeGen::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->elseIfs.empty()) {
        if (!ifStmt->elseBlock) {
            visitSimpleIf(ifStmt);
        } else {
            visitIfWithElse(ifStmt);
        }
    } else {
        visitElseIf(ifStmt);
    }
}

void LgsCodeGen::visitSimpleIf(LgsIfStmt* ifStmt) {
    const auto IRBlockIfTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_NAME_IF_FALSE);

    stack.enterScope(ifStmt);
    cg.builder.CreateCondBr(getIRValue(ifStmt->ifCond), IRBlockIfTrue, ifStmt->IRExitBlock);
    cg.startBlock(IRBlockIfTrue, currentIRFunc);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock, currentIRFunc);
    stack.exitScope();
}

void LgsCodeGen::visitIfWithElse(LgsIfStmt* ifStmt) {
    const auto IRBlockTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockElse = cg.createBlock(BLOCK_NAME_ELSE);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_NAME_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElse);
    cg.startBlock(IRBlockTrue, currentIRFunc);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    // else block
    stack.enterScope(ifStmt);
    cg.startBlock(IRBlockElse, currentIRFunc);
    visitStmtsBlock(ifStmt->elseBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock, currentIRFunc);
    stack.exitScope();
}


void LgsCodeGen::visitElseIf(LgsIfStmt* ifStmt) {
    auto IRBlockTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    auto IRBlockElseIfCheck = cg.createBlock(BLOCK_NAME_ELSE_IF_CHECK);
    const auto IRBlockElse = cg.createBlock(BLOCK_NAME_ELSE);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_NAME_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    cg.startBlock(IRBlockTrue, currentIRFunc);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    for (int i = 0; i < ifStmt->elseIfs.size(); ++i) {
        const auto [expr, stmtBlock] = ifStmt->elseIfs[i];
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockElseIfCheck, currentIRFunc);
        const auto elseIfCondIR = getIRValue(expr);
        IRBlockTrue = cg.createBlock(BLOCK_NAME_ELSE_IF);
        if (i == ifStmt->elseIfs.size() - 1) {
            if (ifStmt->elseBlock) {
                cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElse);
            } else {
                cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, ifStmt->IRExitBlock);
            }
        } else {
            IRBlockElseIfCheck = cg.createBlock(BLOCK_NAME_ELSE_IF_CHECK);
            cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElseIfCheck);
        }
        cg.startBlock(IRBlockTrue, currentIRFunc);
        visitStmtsBlock(stmtBlock);
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }

    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockElse, currentIRFunc);
        visitStmtsBlock(ifStmt->elseBlock);
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }
    cg.startBlock(ifStmt->IRExitBlock, currentIRFunc);
}

void LgsCodeGen::visitPatternMatching(LgsIfStmt* pm) {
    const auto defaultBlock = cg.createBlock(BLOCK_NAME_DEFAULT_CASE);
    const auto exitBlock = cg.createBlock(BLOCK_NAME_EXIT_PATTERN);

    const auto exprIRValue = pm->ifCond->hash(cg);
    SwitchInst* switchInst;
    if (pm->elseBlock) {
        const auto numOfCases = pm->elseIfs.size() + !!pm->elseBlock;
        switchInst = cg.builder.CreateSwitch(exprIRValue, defaultBlock, numOfCases);
    } else {
        switchInst = cg.builder.CreateSwitch(exprIRValue, exitBlock, pm->elseIfs.size());
    }

    std::vector<BasicBlock*> blocks;
    for (size_t i = 0; i < pm->elseIfs.size(); ++i) {
        const auto [expr, stmtsBlock] = pm->elseIfs[i];
        stack.enterScope(pm);
        const auto patterIRValue = expr->hash(cg);
        const auto patternBlock = cg.createBlock(BLOCK_NAME_CASE_PREFIX + std::to_string(i), currentIRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        cg.builder.SetInsertPoint(patternBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    if (pm->elseBlock) {
        stack.enterScope(pm);
        cg.startBlock(defaultBlock, currentIRFunc);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    cg.startBlock(exitBlock, currentIRFunc);
}

void LgsCodeGen::visitCoroutine(const LgsCoroutine* coroutine) {
    const LgsFuncCall* fc = nullptr;
    if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
        fc = coroutine->funcCall;
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
        fc = coroutine->selection->lastExpr()->asFuncCall();
    } else {
        assert(0);
    }
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.addCoro(func, ctx);
}

void LgsCodeGen::visitReturnStmt(LgsReturn* returnStmt) {
    returnStmt->IRValue = returnStmt->expr ? getIRValue(returnStmt->expr) : nullptr;
    const auto currentFunc = stack.currentFunc();
    if (!currentFunc->heapAllocExprs.empty()) {
        returnStmt->parentBlock = cg.builder.GetInsertBlock();
        const auto cleanupBlock = currentFunc->getCleanupBlock(cg);
        cg.builder.CreateBr(cleanupBlock);
    } else {
        if (currentFunc->funcType->rt->isVoid()) {
            cg.builder.CreateRetVoid();
        } else {
            cg.builder.CreateRet(returnStmt->IRValue);
        }
    }
}

void LgsCodeGen::visitContinueStmt() {
    const auto currentLoop = stack.currentLoop();
    currentLoop->incAndJumpToCond(cg);
}

void LgsCodeGen::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        cg.builder.CreateBr(stack.outermostIfStmt()->IRExitBlock);
    } else if (breakStmt->tag != "") {
        cg.builder.CreateBr(stack.findTagExitBlock(breakStmt->tag));
    } else {
        const auto loop = stack.currentLoop();
        cg.builder.CreateBr(loop->IRExitBlock);
    }
}

void LgsCodeGen::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    const LgsFuncCall* fc = nullptr;
    if (deferStmt->funcCall) {
        visitFuncCall(deferStmt->funcCall);
        fc = deferStmt->funcCall;
    } else if (deferStmt->selection) {
        visitSelection(deferStmt->selection);
        fc = deferStmt->selection->lastExpr()->asFuncCall();
    } else {
        assert(0);
    }
    for (const auto& arg : fc->args) {
        visitExpr(arg);
    }
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.addDeferFunc(func, ctx);
}

void LgsCodeGen::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        visitExpr(iter->sizeExpr);
    }
    if (const auto castExpr = dynamic_cast<LgsCast*>(expr)) {
        visitCast(castExpr);
    } else if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    }
    if (expr->type->isHeapAlloc && !expr->asVariable()) {
        stack.currentFunc()->heapAllocExprs.push_back(expr);
    }
    assert(expr->IRValue);
}

void LgsCodeGen::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
    if (const auto func = unaryExpr->asFunc()) return visitLambda(func);
    if (const auto instance = unaryExpr->asInstance()) return visitInstance(instance);
    if (const auto funcCall = unaryExpr->asFuncCall()) return visitFuncCall(funcCall);
    if (const auto strConst = unaryExpr->asStrConst()) return visitStrConst(strConst);
    if (const auto selection = unaryExpr->asSelection()) return visitSelection(selection);
    if (const auto arrayExpr = unaryExpr->asArrayExpr()) return visitArrayExpr(arrayExpr);
    if (const auto hashMap = unaryExpr->asHashMap()) return visitHashMap(hashMap);
    if (const auto iterIndex = unaryExpr->asIterIndex()) return visitIterIndex(iterIndex);
    if (const auto variable = unaryExpr->asVariable()) return visitVariable(variable);
    if (const auto postfixExpr = unaryExpr->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
    if (const auto prefixExpr = unaryExpr->asPrefixExpr()) return visitPrefixExpr(prefixExpr);
    if (const auto vecExpr = unaryExpr->asVectorExpr()) return visitVectorExpr(vecExpr);
    if (const auto intConst = unaryExpr->asIntConst()) return visitIntConst(intConst);
    assert(0);
}

void LgsCodeGen::visitBinaryExpr(LgsBinaryExpr* binExpr) {
    visitExpr(binExpr->left);
    visitExpr(binExpr->right);
    switch (binExpr->op) {
    case ADD: binExpr->IRValue = binExpr->left->addIR(cg, binExpr->right); break;
    case SUB: binExpr->IRValue = binExpr->left->subIR(cg, binExpr->right); break;
    case MUL: binExpr->IRValue = binExpr->left->mulIR(cg, binExpr->right); break;
    case DIV: binExpr->IRValue = binExpr->left->divIR(cg, binExpr->right); break;
    case IN: binExpr->IRValue = binExpr->left->inIR(cg, binExpr->right); break;
    case MOD: binExpr->IRValue = binExpr->left->modIR(cg, binExpr->right); break;
    case EQ: binExpr->IRValue = binExpr->left->eqIR(cg, binExpr->right); break;
    case NE: binExpr->IRValue = binExpr->left->neIR(cg, binExpr->right); break;
    case AND: binExpr->IRValue = binExpr->left->andIR(cg, binExpr->right); break;
    case OR: binExpr->IRValue = binExpr->left->orIR(cg, binExpr->right); break;
    case LT: binExpr->IRValue = binExpr->left->ltIR(cg, binExpr->right); break;
    case GT: binExpr->IRValue = binExpr->left->gtIR(cg, binExpr->right); break;
    case GE: binExpr->IRValue = binExpr->left->geIR(cg, binExpr->right); break;
    case LE: binExpr->IRValue = binExpr->left->leIR(cg, binExpr->right); break;
    case BIT_AND: binExpr->IRValue = binExpr->left->bitAndIR(cg, binExpr->right); break;
    case BIT_OR: binExpr->IRValue = binExpr->left->bitOrIR(cg, binExpr->right); break;
    case BIT_XOR: binExpr->IRValue = binExpr->left->bitXorIR(cg, binExpr->right); break;
    case LSHIFT: binExpr->IRValue = binExpr->left->rshiftIR(cg, binExpr->right); break;
    case RSHIFT: binExpr->IRValue = binExpr->left->lshiftIR(cg, binExpr->right); break;
    case NOOP: assert(0);
    }
}

void LgsCodeGen::visitCast(LgsCast* lgsCast) {
    lgsCast->IRValue = getIRValue(lgsCast->toValue);
}

void LgsCodeGen::visitLambda(LgsFunc* func) {
    cg.savedIP = cg.builder.saveIP();
    visitFunc(func);
    cg.builder.restoreIP(cg.savedIP);
    func->IRValue = func->getIRFunc(cg);
}

void LgsCodeGen::visitIntConst(LgsIntConst* intConst) const {
    if (intConst->type->asBool()) {
        intConst->IRValue = cg.i1(intConst->value);
    } else if (intConst->type->asChar()) {
        intConst->IRValue = cg.i8(intConst->value);
    } else if (intConst->type->asShort()) {
        intConst->IRValue = cg.i16(intConst->value);
    } else if (intConst->type->asInt()) {
        intConst->IRValue = cg.i32(intConst->value);
    } else if (intConst->type->asLong()) {
        intConst->IRValue = cg.i64(intConst->value);
    }
}

void LgsCodeGen::visitArrayExpr(LgsArrayExpr* array) {
    if (array->type->asSArray()) {
        array->IRValue = createConstArray(array);
    } else if (array->type->asDArray()) {
        array->IRValue = createDynamicArray(array);
    }
    else assert(0);
}

void LgsCodeGen::visitHashMap(LgsHashMap* hashMap) {
    const auto mapType = hashMap->type->asMap();
    const auto valueType = mapType->typePair->value;
    const auto elementSize = cg.isize(valueType->getSizeBytes());
    hashMap->IRValue = cg.builder.CreateAlloca(mapType->getMapStruct(cg));
    mapType->initFunc->callIR(cg, {getIRValue(hashMap), elementSize});
    for (const auto element : hashMap->initialElements) {
        visitExpr(element->key);
        visitExpr(element->value);
        mapType->addFunc->call(cg, {hashMap, element->key, element->value});
    }
}

void LgsCodeGen::visitVectorExpr(LgsVectorExpr* vec) {
    const auto ty = vec->type->getIRType(cg);
    vec->IRValue = cg.builder.CreateAlloca(ty);
    cg.builder.CreateStore(ConstantAggregateZero::get(ty), getIRValue(vec));
}


void LgsCodeGen::visitVariable(LgsVariable* variable) {
    switch (variable->ref.symbolType) {
    case VAR_DEC:
        variable->IRValue = getIRValue(variable->ref.varDec);
        break;
    case PARAM:
        variable->IRValue = getIRValue(variable->ref.param);
        break;
    case FUNC:
        variable->IRValue = variable->ref.func->getIRFunc(cg);
        break;
    case OBJECT:
        assert(variable->ref.object->singleton);
        variable->IRValue = getIRValue(variable->ref.object->singleton);
        break;
    case ENUM:
    case ENUM_FIELD:
        variable->IRValue = cg.getIRStr(variable->name);
        break;
    case INTERFACE:
    case GROUP:
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCodeGen::visitSelection(LgsSelection* selection) {
    auto startIndex = 0;
    const auto parentAsVar = selection->exprs.front()->asVariable();
    if (parentAsVar && parentAsVar->ref.symbolType == OBJECT) {
        selection->exprs.front() = parentAsVar->ref.object->singleton;
        startIndex = 1;
    }
    for (int i = startIndex; i < selection->exprs.size() - 1; ++i) {
        const auto parentExpr = selection->exprs[i];
        const auto childExpr = selection->exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            const auto field = parentExpr->type->getField(var->name);
            field->parentIRType = parentExpr->type->getIRType(cg);
            field->parentIRValue = getIRValue(parentExpr);
            if (i > 0) {
                field->parentIRValue = cg.builder.CreateLoad(cg.ptrTy(), field->parentIRValue);
            }
            const auto fieldIR = getIRValue(field);
            childExpr->setIRValue(fieldIR);
        } else {
            getIRValue(childExpr);
        }
    }
    assert(selection->lastExpr()->IRValue);
    selection->IRValue = getIRValue(selection->lastExpr());
}

void LgsCodeGen::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    const auto ft = funcCall->func->funcType;
    if (ft->hasDefaults) {
        const auto diff = ft->params.size() - funcCall->args.size();
        for (int i = diff - 1; i < ft->params.size(); ++i) {
            visitExpr(ft->params[i].expr);
        }
    }
    if (funcCall->ref.symbolType == PARAM) {
        LgsFunc f(funcCall->ref.param->type->asFuncType());
        f.setIRValue(getIRValue(funcCall->ref.param));
        funcCall->IRValue = f.call(cg, funcCall->args);
        return;
    }
    if (ft->isVirtual) {
        funcCall->resolveVirtualFunc(cg);
    }
    funcCall->IRValue = funcCall->func->call(cg, funcCall->args);
}

void LgsCodeGen::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    const auto exprIRVal = getIRValue(prefixExpr->expr);
    switch (prefixExpr->op) {
    case NOT_PREFIX: {
        prefixExpr->IRValue = cg.builder.CreateNot(exprIRVal);
        break;
    }
    case MINUS_PREFIX: {
        const auto zero = ConstantInt::get(prefixExpr->type->getIRType(cg), 0);
        prefixExpr->IRValue = cg.builder.CreateSub(zero, exprIRVal);
        break;
    }
    case SQRT_PREFIX: {
        prefixExpr->IRValue = cg.callSqrt(exprIRVal);
        break;
    }
    }
}

void LgsCodeGen::visitPostfixExpr(LgsPostfixExpr* postfixExpr) const {
    postfixExpr->IRValue = postfixExpr->IncOrDecValue(cg);
}

void LgsCodeGen::visitStrConst(LgsStrConst* strConst) const {
    strConst->IRValue = cg.getIRStr(strConst->value);
}

void LgsCodeGen::visitInstance(LgsInstance* instance) {
    const auto objIRType = instance->obj->getIRType(cg);
    if(instance->obj->singleton) {
        instance->IRValue = cg.createGlobal(objIRType, ConstantAggregateZero::get(objIRType), instance->obj->name);
    } else {
        instance->IRValue = cg.builder.CreateAlloca(objIRType);
    }
    initFields(instance);
    if (!instance->obj->interfaces.empty()) {
        instance->setVirtuals(cg);
    }
}

void LgsCodeGen::initFields(LgsInstance* instance) {
    for (const auto& [argName, arg] : instance->args) {
        const auto exprIR = getIRValue(arg->expr);
        const auto field = instance->obj->getField(argName);
        if (!field) continue;
        field->parentIRValue = getIRValue(instance);
        const auto gep = getIRValue(field);
        cg.builder.CreateStore(exprIR, gep);
    }
}

void LgsCodeGen::visitIterIndex(LgsIterIndex* iterIndex) {
    visitExpr(iterIndex->baseExpr);
    visitExpr(iterIndex->index->from);
    visitExpr(iterIndex->index->to);
    const auto baseExprType = iterIndex->baseExpr->type;
    if (baseExprType->asSArray()) {
        iterIndex->IRValue = iterIndex->loadFromSArray(cg);
    } else if (iterIndex->baseExpr->type->isVector()) {
        iterIndex->IRValue = iterIndex->loadFromVec(cg);
    } else if (const auto arr = baseExprType->asDArray()) {
        iterIndex->IRValue = iterIndex->loadFromDArray(cg, arr);
    } else if (const auto map = baseExprType->asMap()) {
        iterIndex->IRValue = iterIndex->loadFromMap(cg, map);
    } else if (const auto str = baseExprType->asStr()) {
        iterIndex->IRValue = iterIndex->loadFromStr(cg, str);
    } else {
        assert(0);
    }
}

void LgsCodeGen::generateIf(Value* cond, const std::function<void()>& blockStmtCb) {
    const auto IRBlockIfTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockIfFalse = cg.createBlock(BLOCK_NAME_IF_FALSE);
    cg.builder.CreateCondBr(cond, IRBlockIfTrue, IRBlockIfFalse);
    cg.startBlock(IRBlockIfTrue, currentIRFunc);
    blockStmtCb();
    cg.branchAndStartBlock(IRBlockIfFalse, currentIRFunc);
}

void LgsCodeGen::createPrologue(LgsFunc* func) {
    currentIRFunc = func->getIRFunc(cg);
    currentIRFunc->setLinkage(func->funcType->isPublic ? GlobalValue::ExternalLinkage : GlobalValue::PrivateLinkage);
    const auto entryBlock = cg.createBlock(BLOCK_NAME_ENTRY, currentIRFunc);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();
}

void LgsCodeGen::createEpilogue(LgsFunc* func) {
    cg.branchAndStartBlock(func->getCleanupBlock(cg), currentIRFunc);
    currentIRFunc = nullptr;
    if (func->hasDefers) cg.callDefers();

    if (func->heapAllocExprs.empty()) {
        cg.callPopStack();
        return;
    }

    if (func->returnStmts.empty()) {
        cg.callPopStack();
        cg.builder.CreateRetVoid();
        freeHeap(func);
        return;
    }

    if (func->returnStmts.size() == 1) {
        if (func->heapAllocExprs.size() == 1) {
            const auto returnRef = func->returnStmts.front()->expr;
            const auto heapExprRef = func->heapAllocExprs.front();
            if (returnRef->equals(heapExprRef)) {
                cg.callPopStack();
                cg.builder.CreateRet(func->returnStmts.front()->IRValue);
                return;
            }
        }
        freeHeap(func);
        cg.builder.CreateRet(func->returnStmts.front()->IRValue);
        return;
    }

    // multiple return stmts, one or more heap allocations
    auto rt = func->funcType->rt->getIRType(cg);
    if (func->funcType->rt->asDArray()) {
        rt = rt->getPointerTo();
    }
    const auto phi = cg.builder.CreatePHI(rt, func->returnStmts.size());
    for (const auto returnStmt : func->returnStmts) {
        phi->addIncoming(getIRValue(returnStmt->expr), returnStmt->parentBlock);
    }
    cg.callPopStack();
    cg.builder.CreateRet(phi);
    assert(0);
}

void LgsCodeGen::freeHeap(const LgsFunc* func) {
    for (const auto expr : func->heapAllocExprs) {
        expr->type->freeValue(cg, getIRValue(expr));
    }
}

Value* LgsCodeGen::getIRValue(LgsValue* value) {
    if (value->IRValue) return value->IRValue;
    if (const auto expr = dynamic_cast<LgsExpr*>(value)) {
        visitExpr(expr);
    } else if (const auto param = dynamic_cast<LgsParam*>(value)) {
        visitParam(param);
    } else if (const auto field = dynamic_cast<LgsField*>(value)) {
        visitField(field);
    } else {
        assert(0);
    }
    assert(value->IRValue);
    return value->IRValue;
}

Value* LgsCodeGen::createConstArray(const LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asSArray();
    const auto baseIRType = arr->baseType->getIRType(cg);
    const auto arrIRType = ArrayType::get(baseIRType, arr->sizeExpr->getConstInt());
    const auto arrIRPtr = cg.builder.CreateAlloca(arrIRType);
    if (arrayExpr->initialElements.empty()) return arrIRPtr;

    bool allElementsConst = true;
    for (const auto element : arrayExpr->initialElements) {
        visitExpr(element);
        if (!llvm::isa<Constant>(element->IRValue)) {
            allElementsConst = false;
        }
    }

    if (allElementsConst) {
        std::vector<Constant*> IRValues;
        for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
            const auto element = arrayExpr->initialElements[i];
            IRValues.push_back(dyn_cast<Constant>(element->IRValue));
        }
        const auto at = ArrayType::get(baseIRType, arrayExpr->initialElements.size());
        const auto constArr = cg.createConstGlobal(at, ConstantArray::get(at, IRValues));
        cg.callCopyMem(arrIRPtr, constArr, at);
        return arrIRPtr;
    }

    for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
        const auto element = arrayExpr->initialElements[i];
        const auto gep = cg.builder.CreateGEP(arrIRType, arrIRPtr, {cg.i32Zero(), cg.i32(i)});
        cg.builder.CreateStore(element->IRValue, gep);
    }

    return arrIRPtr;
}

Value* LgsCodeGen::createDynamicArray(LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asDArray();
    const auto size = arr->baseType->getSizeBytes();
    const auto elementSize = cg.i64(size);
    const auto arrSize = cg.typeSize(arr->getArrStruct(&cg));
    arrayExpr->IRValue = cg.callMalloc(arrSize.getFixedValue());
    arr->initFunc->callIR(cg, {arrayExpr->IRValue, elementSize});
    for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
        const auto element = arrayExpr->initialElements[i];
        visitExpr(element);
        arr->addFunc->call(cg, {arrayExpr, element});
    }
    return arrayExpr->IRValue;
}

Value* LgsCodeGen::loopEnd(const LgsRangeLoop* loop) {
    visitExpr(loop->endRange);
    return getIRValue(loop->endRange);
}

Value* LgsCodeGen::loopStart(const LgsRangeLoop* loop) {
    if (!loop->startRange) return cg.i32Zero();
    visitExpr(loop->startRange);
    return getIRValue(loop->startRange);
}

Value* LgsCodeGen::getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const {
    if (fc->args.empty()) return cg.null();
    const auto ctx = cg.builder.CreateAlloca(ctxTy);
    for (int i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i]->IRValue;
        cg.storeValueInStruct(dyn_cast<StructType>(ctxTy), ctx, i, v);
    }
    return ctx;
}

Type* LgsCodeGen::getThunkCtxType(const LgsFuncCall* fc) const {
    if (fc->args.empty()) return cg.ptrTy();
    std::vector<Value*> args;
    std::vector<Type*> types;
    for (const auto& arg : fc->args) {
        types.push_back(arg->type->getIRType(cg));
    }
    return cg.getStructType(types, fc->name + "_thunk_type");
}

Function* LgsCodeGen::getThunkFunc(const LgsFuncCall* fc, Type* ctxTy) const {
    auto func = cg.IRModule->getFunction(fc->name + "_thunk");
    if (func) return func;

    cg.savedIP = cg.builder.saveIP();
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy()});
    func = Function::Create(ft, Function::PrivateLinkage, fc->name + "_thunk", cg.IRModule);
    const auto entryBlock = BasicBlock::Create(cg.context, BLOCK_NAME_ENTRY);
    entryBlock->insertInto(func);
    cg.builder.SetInsertPoint(entryBlock);

    std::vector<Value*> args;
    for (int i = 0; i < fc->args.size(); i++) {
        const auto v = cg.loadValueFromStruct(ctxTy, func->arg_begin(), i);
        args.push_back(v);
    }

    const auto deferFunc = fc->func->getIRFunc(cg);
    cg.builder.CreateCall(deferFunc, args);
    cg.builder.CreateRetVoid();

    cg.builder.restoreIP(cg.savedIP);
    return func;
}
