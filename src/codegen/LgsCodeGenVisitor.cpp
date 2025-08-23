#include "codegen/LgsCodeGenVisitor.h"
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
#include "types/LgsTable.h"

#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

void LgsCodeGenVisitor::generate(const LgsAppConfigs& appConfigs, const TargetMachine& targetMachine) {
    cg.setupModule(file, targetMachine.createDataLayout(), appConfigs.debugMode);
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(&file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(&file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(&file)) {
        visitInterface(interfaceFile->interface);
    }
}

void LgsCodeGenVisitor::visitMainFile(LgsMainFile* mainFile) {
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

void LgsCodeGenVisitor::visitObjFile(const LgsObjectFile* objFile) {
    visitObject(objFile->obj);
    for (const auto& [_, method] : objFile->obj->methods) {
        visitFunc(method);
    }
}

void LgsCodeGenVisitor::visitInterfaceFile(const LgsInterfaceFile* interfaceFile) {
    for (const auto& [_, method] : interfaceFile->interface->methods) {
        if (!method->stmtsBlock) continue;
        visitFunc(method);
    }
}

void LgsCodeGenVisitor::visitMainFunc(LgsMainFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    // codeGen->callRuntimeInit();
    if (!func->funcType->params.empty()) func->initMainArgs(cg);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    cg.builder.CreateRet(cg.i32(EXIT_SUCCESS));
    stack.exitScope();
}

void LgsCodeGenVisitor::visitFunc(LgsFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    if (!cg.lastInstTerminator()) cg.builder.CreateRetVoid();
    stack.exitScope();
}

void LgsCodeGenVisitor::visitObject(LgsObject* obj) const {
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

void LgsCodeGenVisitor::visitInterface(LgsInterface* interface) const {
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

void LgsCodeGenVisitor::visitGroup(LgsGroup* group) {
    assert(0);
}

void LgsCodeGenVisitor::visitTable(LgsTable* table) {
    assert(0);
}

void LgsCodeGenVisitor::visitField(LgsField* field) const {
    if (field->parentIRType->isVectorTy()) {
        const auto vec = cg.builder.CreateLoad(field->parentIRType, field->parentIRValue);
        const auto i = cg.isize(field->position);
        field->IRValue = cg.builder.CreateExtractElement(vec, i);
    } else {
        field->IRValue = cg.builder.CreateStructGEP(field->parentIRType, field->parentIRValue, field->position);
    }
}

void LgsCodeGenVisitor::visitParam(LgsParam* param) const {
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

void LgsCodeGenVisitor::visitLoop(LgsForLoop* loopStmt) {
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
    startBlock(loopStmt->IRExitBlock);
    stack.exitScope();
}

void LgsCodeGenVisitor::visitRangeLoop(LgsRangeLoop* loop) {
    loop->iPtr = cg.builder.CreateAlloca(cg.i32Ty());
    cg.builder.CreateStore(loopStart(loop), loop->iPtr);
    cg.builder.CreateBr(loop->IRCondBlock);

    // Condition
    startBlock(loop->IRCondBlock);
    const auto iValue = loop->loadIndex(cg);
    const auto condition = cg.builder.CreateICmpSLT(iValue, loopEnd(loop));
    visitLoopTerminals(loop, iValue);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    startBlock(loop->IRBodyBlock);
    loop->loopVars.front()->setIRValue(iValue);
}

void LgsCodeGenVisitor::visitForeachLoop(LgsForeachLoop* loop) {
    loop->iPtr = cg.builder.CreateAlloca(cg.i32Ty());
    cg.builder.CreateStore(cg.i32Zero(), loop->iPtr);
    branchAndStartBlock(loop->IRCondBlock);
    const auto iterable = loop->iterExpr->type->asIterable();
    if (iterable->asMap()) { // With iterator
        LgsIterator iterator = loop->iterExpr->toIterator();
        iterator.initIterator(cg);
        cg.builder.CreateCondBr(iterator.hasNext(cg), loop->IRBodyBlock, loop->IRExitBlock);
        startBlock(loop->IRBodyBlock);
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
        startBlock(loop->IRBodyBlock);
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

void LgsCodeGenVisitor::visitInfiniteLoop(LgsInfiniteLoop* loop) {
    if (!loop->loopVars.empty()) {
        loop->iPtr = cg.builder.CreateAlloca(cg.i32Ty());
        cg.builder.CreateStore(cg.i32Zero(), loop->iPtr);
    }
    branchAndStartBlock(loop->IRBodyBlock);
    if (!loop->loopVars.empty()) {
        const auto iValue = loop->loadIndex(cg);
        loop->loopVars.front()->setIRValue(iValue);
    }
}

void LgsCodeGenVisitor::visitWhileLoop(LgsWhileLoop* loop) {
    cg.builder.CreateBr(loop->IRCondBlock);
    // Condition
    startBlock(loop->IRCondBlock);
    const auto condition = getIRValue(loop->condExpr);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
    // Body
    startBlock(loop->IRBodyBlock);
}

void LgsCodeGenVisitor::visitLoopTerminals(const LgsRangeLoop* loop, Value* iValue) {
    if (loop->isFirst) {
        loop->isFirst->setIRValue(cg.builder.CreateICmpEQ(iValue, loopStart(loop)));
    }
    if (loop->isLast) {
        const auto decremented = cg.builder.CreateSub(loopEnd(loop), cg.i32(1));
        loop->isLast->setIRValue(cg.builder.CreateICmpEQ(iValue, decremented));
    }
}

void LgsCodeGenVisitor::visitStmt(LgsStmt* stmt) {
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

void LgsCodeGenVisitor::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    for (const auto stmt : stmtsBlock->stmts) {
        visitStmt(stmt);
    }
}

void LgsCodeGenVisitor::visitVarDec(LgsVarDec* varDec) {
    const auto IRType = varDec->type->getIRType(cg);
    const auto exprIRValue = getIRValue(varDec->expr);
    if (varDec->shouldAllocate(IRType)) {
        varDec->IRValue = cg.builder.CreateAlloca(IRType, nullptr, varDec->name);
        cg.builder.CreateStore(exprIRValue, getIRValue(varDec));
    } else {
        varDec->IRValue = exprIRValue;
    }
}

void LgsCodeGenVisitor::visitAssignment(const LgsAssignment* assignment) {
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

void LgsCodeGenVisitor::visitIfStmt(LgsIfStmt* ifStmt) {
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

void LgsCodeGenVisitor::visitSimpleIf(LgsIfStmt* ifStmt) {
    const auto IRBlockIfTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_NAME_IF_FALSE);

    stack.enterScope(ifStmt);
    cg.builder.CreateCondBr(getIRValue(ifStmt->ifCond), IRBlockIfTrue, ifStmt->IRExitBlock);
    startBlock(IRBlockIfTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    branchAndStartBlock(ifStmt->IRExitBlock);
    stack.exitScope();
}

void LgsCodeGenVisitor::visitIfWithElse(LgsIfStmt* ifStmt) {
    const auto IRBlockTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockElse = cg.createBlock(BLOCK_NAME_ELSE);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_NAME_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElse);
    startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    // else block
    stack.enterScope(ifStmt);
    startBlock(IRBlockElse);
    visitStmtsBlock(ifStmt->elseBlock);
    branchAndStartBlock(ifStmt->IRExitBlock);
    stack.exitScope();
}


void LgsCodeGenVisitor::visitElseIf(LgsIfStmt* ifStmt) {
    auto IRBlockTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    auto IRBlockElseIfCheck = cg.createBlock(BLOCK_NAME_ELSE_IF_CHECK);
    const auto IRBlockElse = cg.createBlock(BLOCK_NAME_ELSE);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_NAME_IF_FALSE);

    // if block
    stack.enterScope(ifStmt);
    const auto ifCondIR = getIRValue(ifStmt->ifCond);
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    for (int i = 0; i < ifStmt->elseIfs.size(); ++i) {
        const auto [expr, stmtBlock] = ifStmt->elseIfs[i];
        stack.enterScope(ifStmt);
        startBlock(IRBlockElseIfCheck);
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
        startBlock(IRBlockTrue);
        visitStmtsBlock(stmtBlock);
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }

    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        startBlock(IRBlockElse);
        visitStmtsBlock(ifStmt->elseBlock);
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }
    startBlock(ifStmt->IRExitBlock);
}

void LgsCodeGenVisitor::visitPatternMatching(LgsIfStmt* pm) {
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
        const auto IRFunc = stack.currentFunc()->getIRFunc(cg);
        const auto patternBlock = cg.createBlock(BLOCK_NAME_CASE_PREFIX + std::to_string(i), IRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        cg.builder.SetInsertPoint(patternBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    if (pm->elseBlock) {
        stack.enterScope(pm);
        startBlock(defaultBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    startBlock(exitBlock);

}

void LgsCodeGenVisitor::visitCoroutine(const LgsCoroutine* coroutine) {
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

void LgsCodeGenVisitor::visitReturnStmt(LgsReturn* returnStmt) {
    returnStmt->IRValue = returnStmt->expr ? getIRValue(returnStmt->expr) : nullptr;
    const auto currentFunc = stack.currentFunc();
    const auto currentStmtsBlock = stack.currentFunc();
    if (currentStmtsBlock->needsCleanup()) {
        returnStmt->parentBlock = cg.builder.GetInsertBlock();
        const auto cleanupBlock = currentStmtsBlock->getCleanupBlock(cg);
        cg.builder.CreateBr(cleanupBlock);
    } else {
        if (currentFunc->funcType->rt->isVoid()) {
            cg.builder.CreateRetVoid();
        } else {
            cg.builder.CreateRet(returnStmt->IRValue);
        }
    }
}

void LgsCodeGenVisitor::visitContinueStmt() {
    const auto currentLoop = stack.currentLoop();
    currentLoop->incAndJumpToCond(cg);
}

void LgsCodeGenVisitor::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        cg.builder.CreateBr(stack.outermostIfStmt()->IRExitBlock);
    } else {
        const auto loop = stack.currentLoop();
        cg.builder.CreateBr(loop->IRExitBlock);
    }
}

void LgsCodeGenVisitor::visitDeferStmt(const LgsDeferStmt* deferStmt) {
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

void LgsCodeGenVisitor::visitExpr(LgsExpr* expr) {
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
    assert(expr->IRValue);
}

void LgsCodeGenVisitor::visitUnaryExpr(LgsUnaryExpr* unaryExpr) {
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

void LgsCodeGenVisitor::visitBinaryExpr(LgsBinaryExpr* binExpr) {
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

void LgsCodeGenVisitor::visitCast(LgsCast* lgsCast) {
    lgsCast->IRValue = getIRValue(lgsCast->toValue);
}

void LgsCodeGenVisitor::visitLambda(LgsFunc* func) {
    cg.savedIP = cg.builder.saveIP();
    visitFunc(func);
    cg.builder.restoreIP(cg.savedIP);
    func->IRValue = func->getIRFunc(cg);
}

void LgsCodeGenVisitor::visitIntConst(LgsIntConst* intConst) const {
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

void LgsCodeGenVisitor::visitArrayExpr(LgsArrayExpr* array) {
    if (array->type->asSArray()) {
        array->IRValue = createConstArray(array);
    } else if (array->type->asDArray()) {
        array->IRValue = createDynamicArray(array);
    }
    else assert(0);
}

Value* LgsCodeGenVisitor::createConstArray(const LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asSArray();
    const auto baseType = arr->baseType;
    const auto baseIRType = baseType->getIRType(cg);
    const auto arrIRType = ArrayType::get(baseIRType, arr->sizeExpr->getConstInt());
    const auto arrIRPtr = cg.builder.CreateAlloca(arrIRType);
    if (arrayExpr->initialElements.empty()) return arrIRPtr;
    for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
        const auto element = arrayExpr->initialElements[i];
        visitExpr(element);
        const auto gep = cg.builder.CreateGEP(arrIRType, arrIRPtr, {cg.i32Zero(), cg.i32(i)});
        cg.builder.CreateStore(element->IRValue, gep);
    }
    return arrIRPtr;
}

Value* LgsCodeGenVisitor::createDynamicArray(LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asDArray();
    const auto size = arr->baseType->getSizeBytes();
    const auto elementSize = cg.i64(size);
    const auto arrSize = cg.typeSize(arr->getArrStruct(&cg));
    arrayExpr->IRValue = cg.callMalloc(arrSize.getFixedValue());
    arr->initFunc->callIR(cg, {arrayExpr->IRValue, elementSize});
    for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
        const auto element = arrayExpr->initialElements[i];
        visitExpr(element);
    }
    return arrayExpr->IRValue;
}


void LgsCodeGenVisitor::visitHashMap(LgsHashMap* hashMap) {
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

void LgsCodeGenVisitor::visitVectorExpr(LgsVectorExpr* vec) {
    const auto ty = vec->type->getIRType(cg);
    vec->IRValue = cg.builder.CreateAlloca(ty);
    cg.builder.CreateStore(ConstantAggregateZero::get(ty), getIRValue(vec));
}

void LgsCodeGenVisitor::visitVariable(LgsVariable* variable) {
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
    case TABLE:
        variable->IRValue = variable->ref.table->instance->IRValue;
        break;
    case INTERFACE:
    case GROUP:
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCodeGenVisitor::visitSelection(LgsSelection* selection) {
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

void LgsCodeGenVisitor::visitFuncCall(LgsFuncCall* funcCall) {
    for (const auto& arg : funcCall->args) {
        visitExpr(arg);
    }
    if (funcCall->ref.symbolType == PARAM) {
        LgsFunc f(funcCall->ref.param->type->asFuncType());
        f.setIRValue(getIRValue(funcCall->ref.param));
        funcCall->IRValue = f.call(cg, funcCall->args);
        return;
    }
    if (funcCall->func->funcType->isVirtual) {
        funcCall->resolveVirtualFunc(cg);
    }
    funcCall->IRValue = funcCall->func->call(cg, funcCall->args);
}

void LgsCodeGenVisitor::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
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

void LgsCodeGenVisitor::visitPostfixExpr(LgsPostfixExpr* postfixExpr) const {
    postfixExpr->IRValue = postfixExpr->IncOrDecValue(cg);
}

void LgsCodeGenVisitor::visitStrConst(LgsStrConst* strConst) const {
    strConst->IRValue = cg.getIRStr(strConst->value);
}

void LgsCodeGenVisitor::visitInstance(LgsInstance* instance) const {
    if (instance->table) return instance->createIRTable(cg);
    const auto objIRType = instance->obj->getIRType(cg);
    if(instance->obj->singleton) {
        instance->IRValue = cg.createGlobal(objIRType, ConstantAggregateZero::get(objIRType), instance->obj->name);
    } else {
        instance->IRValue = cg.builder.CreateAlloca(objIRType);
    }
    instance->initFields(cg);
    if (!instance->obj->interfaces.empty()) {
        instance->setVirtuals(cg);
    }
}

void LgsCodeGenVisitor::visitIterIndex(LgsIterIndex* iterIndex) {
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

Value* LgsCodeGenVisitor::getIRValue(LgsValue* value) {
    if (value->IRValue) return value->IRValue;
    if (const auto expr = dynamic_cast<LgsExpr*>(value)) {
        visitExpr(expr);
    } else if (const auto param = dynamic_cast<LgsParam*>(value)) {
        visitParam(param);
    } else {
        assert(0);
    }
    assert(value->IRValue);
    return value->IRValue;
}

Value* LgsCodeGenVisitor::loopEnd(const LgsRangeLoop* loop) {
    visitExpr(loop->endRange);
    return getIRValue(loop->endRange);
}

Value* LgsCodeGenVisitor::loopStart(const LgsRangeLoop* loop) {
    if (!loop->startRange) return cg.i32Zero();
    visitExpr(loop->startRange);
    return getIRValue(loop->startRange);
}

void LgsCodeGenVisitor::generateIf(Value* cond, const std::function<void()>& blockStmtCb) {
    const auto IRBlockIfTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockIfFalse = cg.createBlock(BLOCK_NAME_IF_FALSE);
    cg.builder.CreateCondBr(cond, IRBlockIfTrue, IRBlockIfFalse);
    startBlock(IRBlockIfTrue);
    blockStmtCb();
    branchAndStartBlock(IRBlockIfFalse);
}

void LgsCodeGenVisitor::startBlock(BasicBlock* block) {
    block->insertInto(stack.currentFunc()->getIRFunc(cg));
    cg.builder.SetInsertPoint(block);
}

void LgsCodeGenVisitor::branchAndStartBlock(BasicBlock* block) {
    cg.branchIfNeeded(block);
    startBlock(block);
}

void LgsCodeGenVisitor::createPrologue(LgsFunc* func) const {
    const auto IRFunc = func->getIRFunc(cg);
    IRFunc->setLinkage(func->funcType->isPublic ? GlobalValue::ExternalLinkage : GlobalValue::PrivateLinkage);
    const auto entryBlock = cg.createBlock(BLOCK_NAME_ENTRY, IRFunc);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();
}

void LgsCodeGenVisitor::createEpilogue(LgsFunc* func) {
    branchAndStartBlock(func->getCleanupBlock(cg));
    if (func->hasDefers) {
        cg.callDefers();
    }
    // 0 return, 0 heap
    // 1 return, 0 heap
    // >1 return, 0 heap
    if (!func->needsCleanup()) {
        cg.callPopStack();
        return;
    }
    // 0 return, 1 heap
    // 0 return, >1 heap
    if (func->returnStmts.empty()) {
        cg.callPopStack();
        freeHeap(func);
        return;
    }
    // 1 return, >1 heap
    // >1 return, >1 heap
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
}

void LgsCodeGenVisitor::freeHeap(const LgsFunc* func) {
    for (const auto expr : func->heapAllocExprs) {
        expr->type->freeValue(cg, getIRValue(expr));
    }
}

Function* LgsCodeGenVisitor::getThunkFunc(const LgsFuncCall* fc, Type* ctxTy) {
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

Value* LgsCodeGenVisitor::getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const {
    if (fc->args.empty()) return cg.null();
    const auto ctx = cg.builder.CreateAlloca(ctxTy);
    for (int i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i]->IRValue;
        cg.storeValueInStruct(dyn_cast<StructType>(ctxTy), ctx, i, v);
    }
    return ctx;
}

Type* LgsCodeGenVisitor::getThunkCtxType(const LgsFuncCall* fc) const {
    if (fc->args.empty()) return cg.ptrTy();
    std::vector<Value*> args;
    std::vector<Type*> types;
    for (const auto& arg : fc->args) {
        types.push_back(arg->type->getIRType(cg));
    }
    return cg.getStructType(types, fc->name + "_thunk_type");
}
