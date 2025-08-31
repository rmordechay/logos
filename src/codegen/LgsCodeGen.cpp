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
#include "exprs/unary/constants/LgsFloatConst.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "files/LgsMainFile.h"
#include "funcs/LgsMainFunc.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/iterables/LgsDArray.h"
#include "types/LgsInterface.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

void LgsCodeGen::generate(const LgsAppConfigs& appConfigs, TargetMachine& targetMachine) {
    cg.targetMachine = &targetMachine;
    cg.setupModule(file, appConfigs.debugMode);
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(&file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(&file)) {
        visitObjFile(objFile);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(&file)) {
        visitInterfaceFile(interfaceFile);
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
    if (!func->funcType->params.empty()) initMainArgs(func);
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
        const auto ptr = field->type->asObject() || field->type->asFuncType() || field->type->asInterface() || field->type->asDArray();
        if (ptr) {
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
    if (const auto vec = field->type->asVec()) {
        std::vector<int> mask(vec->dim);
        for (unsigned i = 0; i < vec->dim; i++) {
            mask[i] = LgsVec::getComponentIndex(field->name[i]);
        }
        const ArrayRef maskRef(mask);
        const auto parentLoaded = cg.builder.CreateLoad(field->parentIRType, field->parentIRValue);
        const auto newVec = cg.builder.CreateShuffleVector(parentLoaded, UndefValue::get(field->parentIRType), maskRef);
        field->IRValue = cg.builder.CreateAlloca(field->parentIRType);
        cg.builder.CreateStore(newVec, field->IRValue);
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

void LgsCodeGen::visitLoop(LgsForLoop* loop) {
    stack.enterScope(loop);
    loop->setBlocks(cg);
    if (const auto rangeLoop = loop->asRangeLoop()) {
        visitRangeLoop(rangeLoop);
    } else if (const auto foreachLoop = loop->asForeachLoop()) {
        visitForeachLoop(foreachLoop);
    } else if (const auto infiniteLoop = loop->asInfiniteLoop()) {
        visitInfiniteLoop(infiniteLoop);
    } else if (const auto whileLoop = loop->asWhileLoop()) {
        visitWhileLoop(whileLoop);
    } else {
        assert(0);
    }
    visitStmtsBlock(loop->stmtsBlock);
    loop->incAndJumpToCond(cg);
    cg.startBlock(loop->IRExitBlock, currentIRFunc);
    stack.exitScope();
}

void LgsCodeGen::visitRangeLoop(LgsRangeLoop* loop) {
    visitExpr(loop->startRange);
    visitExpr(loop->endRange);
    loop->iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    const auto loopStart = cg.builder.CreateSExt(loop->loopStart(cg), cg.sizeTy());
    cg.builder.CreateStore(loopStart, loop->iPtr);
    cg.builder.CreateBr(loop->IRCondBlock);

    // Condition
    cg.startBlock(loop->IRCondBlock, currentIRFunc);
    loop->iValue = loop->loadIndex(cg);
    const auto loopEnd = cg.builder.CreateSExt(loop->loopEnd(cg), cg.sizeTy());
    const auto condition = cg.builder.CreateICmpSLT(loop->iValue, loopEnd);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock, currentIRFunc);
    if (!loop->loopVars.empty()) {
        loop->loopVars.front()->setIRValue(loop->iValue);
    }
}

void LgsCodeGen::visitForeachLoop(LgsForeachLoop* loop) {
    loop->iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    cg.builder.CreateStore(cg.sizeZero(), loop->iPtr);
    cg.branchAndStartBlock(loop->IRCondBlock, currentIRFunc);

    visitExpr(loop->iterExpr);
    const auto iterable = loop->iterExpr->type->asIterable();
    if (iterable->asMap()) assert(0);

    loop->iValue = loop->loadIndex(cg);
    auto loopEnd = loop->loopEnd(cg);
    loopEnd = cg.builder.CreateSExt(loopEnd, cg.sizeTy());
    const auto condition = cg.builder.CreateICmpSLT(loop->iValue, loopEnd);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    cg.startBlock(loop->IRBodyBlock, currentIRFunc);
    loop->iterPtr = getIRValue(loop->iterExpr);
    if (const auto str = iterable->asStr()) {
        const auto gep = cg.builder.CreateGEP(str->getIRBaseType(&cg), loop->iterPtr, {cg.i32Zero(), loop->iValue});
        loop->loopVars[0]->setIRValue(gep);
    } else if (const auto dArr = iterable->asDArray()) {
        const auto element = dArr->getFunc->callIR(cg, {loop->iterPtr, loop->iValue});
        loop->loopVars[0]->setIRValue(element);
    } else if (const auto sArr = iterable->asSArray()) {
        const auto gep = cg.builder.CreateGEP(sArr->getIRType(cg), loop->iterPtr, {cg.i32Zero(), loop->iValue});
        loop->loopVars[0]->setIRValue(gep);
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitInfiniteLoop(const LgsInfiniteLoop* loop) const {
    cg.branchAndStartBlock(loop->IRBodyBlock, currentIRFunc);
}

void LgsCodeGen::visitWhileLoop(const LgsWhileLoop* loop) {
    cg.builder.CreateBr(loop->IRCondBlock);
    // Condition
    cg.startBlock(loop->IRCondBlock, currentIRFunc);
    const auto condition = getIRValue(loop->condExpr);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
    // Body
    cg.startBlock(loop->IRBodyBlock, currentIRFunc);
}

void LgsCodeGen::visitLoopMetaVar(LgsLoopMetaVar* metaVar) {
    const auto loop = stack.currentLoop();
    const auto iValue = loop->iValue;
    switch (metaVar->varType) {
    case FOR_I:
        metaVar->IRValue = iValue;
        break;
    case FOR_IS_FIRST: {
        const auto loopStart = cg.builder.CreateSExt(loop->loopStart(cg), cg.sizeTy());
        metaVar->setIRValue(cg.builder.CreateICmpEQ(iValue, loopStart));
    }
        break;
    case FOR_IS_LAST: {
        const auto loopEnd = cg.builder.CreateSExt(loop->loopEnd(cg), cg.sizeTy());
        const auto decremented = cg.builder.CreateSub(loopEnd, cg.usize(1));
        metaVar->setIRValue(cg.builder.CreateICmpEQ(iValue, decremented));
        break;
    }
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
    if (const auto ioStmt = stmt->asIOStmt()) return visitIOStmt(ioStmt);
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
    visitExpr(assignment->lValue);
    visitExpr(assignment->rValue);
    Value* results = nullptr;
    switch (assignment->assignmentType) {
    case ASSIGN: assignment->lValue->assign(cg, assignment->rValue); return;
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

void LgsCodeGen::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitVarDec(ioStmt->varDec);
    visitStmtsBlock(ioStmt->stmtsBlock);
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
            cg.builder.CreateRet(getIRValue(returnStmt));
        }
    }
}

void LgsCodeGen::visitContinueStmt() {
    stack.currentLoop()->incAndJumpToCond(cg);
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
    if (const auto unaryExpr = dynamic_cast<LgsUnaryExpr*>(expr)) {
        visitUnaryExpr(unaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        assert(0);
    }
    if (expr->type->isHeapAlloc && !expr->asVariable()) {
        stack.currentFunc()->heapAllocExprs.push_back(expr);
    }
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
    if (const auto floatConst = unaryExpr->asFloatConst()) return visitFloatConst(floatConst);
    if (const auto loopMetaVar = unaryExpr->asLoopMetaVar()) return visitLoopMetaVar(loopMetaVar);
    if (const auto typeExpr = unaryExpr->asTypeExpr()) return visitTypeExpr(typeExpr);
    if (const auto cast = unaryExpr->asCast()) return visitCast(cast);
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
    visitExpr(lgsCast->toValue);
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
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitFloatConst(LgsFloatConst* floatConst) const {
    if (floatConst->type->asFloat()) {
        floatConst->IRValue = cg.floatv(floatConst->value);
    } else if (floatConst->type->asDouble()) {
        floatConst->IRValue = cg.doublev(floatConst->value);
    } else {
        assert(0);
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
    const auto elementSize = cg.usize(valueType->getSizeBytes());
    const auto arrSize = cg.typeSize(mapType->getMapStruct(cg));
    hashMap->IRValue = cg.callMalloc(arrSize.getFixedValue());
    mapType->initFunc->callIR(cg, {getIRValue(hashMap), elementSize});
    for (const auto element : hashMap->initialElements) {
        visitExpr(element->key);
        visitExpr(element->value);
        mapType->addFunc->call(cg, {hashMap, element->key, element->value});
    }
}

void LgsCodeGen::visitVectorExpr(LgsVectorExpr* vectorExpr) {
    const auto ty = vectorExpr->type->getIRType(cg);
    vectorExpr->IRValue = cg.builder.CreateAlloca(ty);
    if (!vectorExpr->args.empty()) {
        Value* vectorValue = UndefValue::get(ty);
        for (size_t i = 0; i < vectorExpr->args.size(); ++i) {
            const auto elementValue = getIRValue(vectorExpr->args[i]);
            vectorValue = cg.builder.CreateInsertElement(vectorValue, elementValue, ConstantInt::get(Type::getInt32Ty(cg.context), i));
        }
        cg.builder.CreateStore(vectorValue, vectorExpr->IRValue);
    } else {
        cg.builder.CreateStore(ConstantAggregateZero::get(ty), vectorExpr->IRValue);
    }
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
    case FIELD:
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
    const auto parentAsVar = selection->exprs.front()->asVariable();
    if (parentAsVar && parentAsVar->ref.symbolType == OBJECT) {
        assert(0);
    }

    for (int i = 0; i < selection->exprs.size() - 1; ++i) {
        const auto parentExpr = selection->exprs[i];
        const auto childExpr = selection->exprs[i + 1];
        if (const auto var = childExpr->asVariable()) {
            const auto field = parentExpr->type->getField(var->name);
            field->parentIRType = parentExpr->type->getIRType(cg);
            field->parentIRValue = getIRValue(parentExpr);
            visitField(field);
            childExpr->setIRValue(field->IRValue);
        } else if (childExpr->asFuncCall()) {
            getIRValue(childExpr);
        } else if (const auto iterIndex = childExpr->asIterIndex()) {
            assert(0);
        } else {
            assert(0);
        }
    }
    assert(selection->lastExpr()->IRValue);
    selection->IRValue = getIRValue(selection->lastExpr());
}

void LgsCodeGen::visitFuncCall(LgsFuncCall* funcCall) {
    const bool isMethod = funcCall->func->funcType->isMethod;
    for (int i = isMethod; i < funcCall->args.size(); ++i) {
        visitExpr(funcCall->args[i]);
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

void LgsCodeGen::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    visitExpr(postfixExpr->expr);
    const auto exprIRValue = postfixExpr->expr->IRValue;
    const auto exprIRType = postfixExpr->expr->type->getIRType(cg);
    const auto exprLoad = postfixExpr->expr->loadIR(cg);
    const auto oneConst = ConstantInt::get(exprIRType, 1);
    switch (postfixExpr->op) {
    case INC:
        postfixExpr->IRValue = cg.builder.CreateAdd(exprLoad, oneConst);
        break;
    case DEC:
        postfixExpr->IRValue = cg.builder.CreateSub(exprLoad, oneConst);
        break;
    }
    cg.builder.CreateStore(postfixExpr->IRValue, exprIRValue);
}

void LgsCodeGen::visitStrConst(LgsStrConst* strConst) const {
    strConst->IRValue = cg.getIRStr(strConst->value);
}

void LgsCodeGen::visitTypeExpr(LgsTypeExpr* typeExpr) {
    assert(0);
}

void LgsCodeGen::visitInstance(LgsInstance* instance) {
    visitObject(instance->obj);
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

void LgsCodeGen::visitIterIndex(LgsIterIndex* iterIndex) {
    visitExpr(iterIndex->baseExpr);
    visitExpr(iterIndex->index->from);
    visitExpr(iterIndex->index->to);
    iterIndex->IRValue = iterIndex->baseExpr->IRValue;
}

void LgsCodeGen::initFields(LgsInstance* instance) {
    std::unordered_set<std::string> visited;
    for (const auto& [argName, arg] : instance->args) {
        visited.insert(argName);
        const auto exprIR = getIRValue(arg->expr);
        const auto field = instance->obj->getField(argName);
        assert(field);
        field->parentIRValue = getIRValue(instance);
        const auto gep = getIRValue(field);
        cg.builder.CreateStore(exprIR, gep);
    }
    for (const auto& field : instance->obj->fields) {
        if (visited.count(field->name)) continue;
        field->parentIRValue = getIRValue(instance);
        const auto zeroValue = field->type->getZeroValue();
        const auto zeroIRValue = getIRValue(zeroValue);
        cg.builder.CreateStore(zeroIRValue, getIRValue(field));
    }
}

void LgsCodeGen::initMainArgs(LgsMainFunc* mainFunc) {
    auto& builder = cg.builder;
    const std::vector<Type*> structFields{cg.i64Ty(), cg.i32Ty(), cg.i32Ty(), cg.ptrTy()};
    const auto arrStruct = cg.getStructType(structFields, LgsDArray::name);
    mainFunc->mainArgs->IRValue = builder.CreateAlloca(arrStruct);
    mainFunc->initArgsFunc->callIR(cg, {getIRValue(mainFunc->mainArgs), mainFunc->argc, mainFunc->argv});
    mainFunc->funcType->params[0].setIRValue(getIRValue(mainFunc->mainArgs));
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
        // freeHeap(func);
        cg.callPopStack();
        return;
    }

    if (func->returnStmts.size() == 1) {
        if (func->heapAllocExprs.size() == 1) {
            const auto returnRef = func->returnStmts.front()->expr;
            const auto heapExprRef = func->heapAllocExprs.front();
            if (returnRef->equals(heapExprRef)) {
                cg.callPopStack();
                cg.builder.CreateRet(getIRValue(func->returnStmts.front()));
                return;
            }
        }
        freeHeap(func);
        cg.builder.CreateRet(getIRValue(func->returnStmts.front()));
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

void LgsCodeGen::generateIf(Value* cond, const std::function<void()>& blockStmtCb) const {
    const auto IRBlockIfTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockIfFalse = cg.createBlock(BLOCK_NAME_IF_FALSE);
    cg.builder.CreateCondBr(cond, IRBlockIfTrue, IRBlockIfFalse);
    cg.startBlock(IRBlockIfTrue, currentIRFunc);
    blockStmtCb();
    cg.branchAndStartBlock(IRBlockIfFalse, currentIRFunc);
}

Value* LgsCodeGen::createConstArray(const LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asSArray();
    const auto baseIRType = arr->baseType->getIRType(cg);
    const auto arrIRType = ArrayType::get(baseIRType, arr->sizeExpr->getConstInt());
    const auto arrIRPtr = cg.builder.CreateAlloca(arrIRType);
    if (arrayExpr->initialElements.empty()) return arrIRPtr;
    if (allArgsAreConst(arrayExpr->initialElements)) {
        std::vector<Constant*> IRValues;
        for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
            const auto element = arrayExpr->initialElements[i];
            IRValues.push_back(dyn_cast<Constant>(getIRValue(element)));
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
    const auto arrSize = cg.typeSize(arr->getArrStruct(cg));
    arrayExpr->IRValue = cg.callMalloc(arrSize.getFixedValue());
    arr->initFunc->callIR(cg, {arrayExpr->IRValue, elementSize});
    for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
        const auto element = arrayExpr->initialElements[i];
        visitExpr(element);
        arr->addFunc->call(cg, {arrayExpr, element});
    }
    return getIRValue(arrayExpr);
}

void LgsCodeGen::initIterator(LgsIterator* iterator) {
    LgsFunc iterInitFunc{"initIter", &LGS_VOID, {iterator->type, &LGS_ANY}};
    const auto structType = cg.getStructType({
        cg.ptrTy(),
        cg.i64Ty(),
        cg.ptrTy(),
        cg.ptrTy(),
        cg.ptrTy(),
        cg.ptrTy()
    }, iterator->name);
    iterator->IRValue = cg.builder.CreateAlloca(structType);
    iterInitFunc.callIR(cg, {getIRValue(iterator->baseExpr), getIRValue(iterator)});
}

Value* LgsCodeGen::iterNext(LgsIterator* iterator) {
    LgsFunc iterInitFunc{"next", &LGS_ANY, {&LGS_ANY}};
    return iterInitFunc.callIR(cg, {getIRValue(iterator)});
}

Value* LgsCodeGen::iterHasNext(LgsIterator* iterator) {
    LgsFunc iterInitFunc{"hasNext", &LGS_BOOL, {&LGS_ANY}};
    return iterInitFunc.callIR(cg, {getIRValue(iterator)});
}

Value* LgsCodeGen::getIRValue(LgsValue* value) {
    if (value->IRValue) return value->IRValue;
    if (const auto expr = dynamic_cast<LgsExpr*>(value)) {
        visitExpr(expr);
    } else if (const auto stmt = dynamic_cast<LgsStmt*>(value)) {
        visitStmt(stmt);
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

bool LgsCodeGen::allArgsAreConst(const std::vector<LgsExpr*>& args) {
    bool allElementsConst = true;
    for (const auto element : args) {
        visitExpr(element);
        if (!llvm::isa<Constant>(getIRValue(element))) {
            allElementsConst = false;
        }
    }
    return allElementsConst;
}