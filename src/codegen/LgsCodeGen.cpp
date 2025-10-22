#include "codegen/LgsCodeGen.h"
#include "builtins/LgsTest.h"
#include "exprs/LgsArrayExpr.h"
#include "funcs/LgsCoroutine.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsJson.h"
#include "exprs/LgsNull.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsTypeExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsEnum.h"
#include "files/LgsMainFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsMainFunc.h"
#include "stmts/LgsBreak.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsDeferStmt.h"
#include "stmts/LgsVarDec.h"
#include "types/iterables/LgsDArray.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "stmts/LgsSwitch.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsSize.h"
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

std::atomic<size_t> LgsCodeGen::namesCounter{0};

void LgsCodeGen::generate(const LgsAppConfigs& appConfigs, TargetMachine& targetMachine) {
    cg.targetMachine = &targetMachine;
    cg.setupModule(file, appConfigs.debugMode);
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(&file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(&file)) {
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(&file)) {
        visitInterface(interfaceFile->interface);
    } else if (const auto testFile = dynamic_cast<LgsTestFile*>(&file)) {
        visitTestFile(testFile);
    }
}

void LgsCodeGen::visitMainFile(LgsMainFile* mainFile) {
    for (const auto interface : mainFile->interfaces) {
        visitInterface(interface);
    }
    for (const auto object : mainFile->objects) {
        visitObject(object);
    }
    for (const auto [_, func] : mainFile->funcs) {
        if (const auto mainFunc = dynamic_cast<LgsMainFunc*>(func)) {
            visitMainFunc(mainFunc);
        } else {
            visitFunc(func);
        }
    }
}

void LgsCodeGen::visitInterface(const LgsInterface* interface) {
    for (const auto& [_, method] : interface->methods) {
        if (!method->stmtsBlock) continue;
        visitFunc(method);
    }
}

void LgsCodeGen::visitTestFile(const LgsTestFile* testFile) {
    for (const auto& func : testFile->funcs) {
        visitFunc(func);
    }
    for (const auto& test : testFile->tests) {
        visitFunc(test);
    }
}

void LgsCodeGen::visitObject(LgsObject* obj) {
    if(const auto singleton = obj->singleton) {
        const auto objIRType = obj->getIRType(cg);
        singleton->IRValue = cg.IRModule->getGlobalVariable(obj->name);
        if (!singleton->IRValue) {
            const auto zeroInit = ConstantAggregateZero::get(objIRType);
            singleton->IRValue = cg.createGlobal(objIRType, zeroInit, obj->name);
        }
    }
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
}

void LgsCodeGen::visitMainFunc(LgsMainFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    initMainArgs(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    cg.callLgsFunc("runtime_close", cg.voidTy());
    cg.builder.CreateRet(cg.i32(EXIT_SUCCESS));
    stack.exitScope();
}

void LgsCodeGen::visitFunc(LgsFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    if (func->funcType->rt->isVoid() && !cg.lastInstTerminator()) {
        cg.builder.CreateRetVoid();
    }
    stack.exitScope();
}

void LgsCodeGen::visitField(LgsField* field) const {
    if (field->IRValue) return;
    if (const auto vec = field->type->asVec()) {
        std::vector<int> mask(vec->vectorDim);
        for (unsigned i = 0; i < vec->vectorDim; i++) {
            mask[i] = LgsVec::getComponentIndex(field->name[i]);
        }
        const ArrayRef maskRef(mask);
        const auto vecType = field->type->getIRType(cg);
        field->IRValue = cg.builder.CreateAlloca(vecType);
        const auto l = cg.builder.CreateLoad(field->parentIRType, field->parentIRValue);
        const auto newVec = cg.builder.CreateShuffleVector(l, UndefValue::get(field->parentIRType), maskRef);
        cg.builder.CreateStore(newVec, field->IRValue);
    } else {
        assert(field->parentIRType && field->parentIRValue);
        field->IRValue = cg.builder.CreateStructGEP(field->parentIRType, field->parentIRValue, field->position);
        if (field->expr) {
            field->expr->destPtrValue = field->IRValue;
        }
    }
}

void LgsCodeGen::visitParam(LgsParam* param) {
    visitExpr(param->expr);
    if (param->isVariadic) {
        if (param->vaList) {
            param->IRValue = param->vaList;
            return;
        }
        param->vaList = cg.builder.CreateAlloca(cg.builder.getPtrTy());
        const auto vaStart = Intrinsic::getDeclaration(cg.IRModule, Intrinsic::vastart, {cg.builder.getPtrTy()});
        cg.builder.CreateCall(vaStart, {param->vaList});
        param->IRValue = param->vaList;
    }
}

void LgsCodeGen::visitStmt(LgsStmt* stmt) {
    if (const auto ifStmt = stmt->asIfStmt()) return visitIfStmt(ifStmt);
    if (const auto pattern = stmt->asSwitch()) return visitSwitch(pattern);
    if (const auto varDec = stmt->asVarDec()) return visitVarDec(varDec);
    if (const auto loopStmt = stmt->asLoop()) return visitLoop(loopStmt);
    if (const auto coroutine = stmt->asCoroutine()) return visitCoroutine(coroutine);
    if (const auto deferStmt = stmt->asDefer()) return visitDeferStmt(deferStmt);
    if (const auto assignment = stmt->asAssignment()) return visitAssignment(assignment);
    if (const auto funcCall = stmt->asFuncCall()) return visitFuncCall(funcCall);
    if (const auto postfixExpr = stmt->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
    if (const auto postfixExpr = stmt->asExpr()) return visitExpr(postfixExpr);
    if (const auto selection = stmt->asSelection()) return visitSelection(selection);
    if (const auto ioStmt = stmt->asIOStmt()) return visitIOStmt(ioStmt);
    if (const auto returnStmt = stmt->asReturn()) return visitReturnStmt(returnStmt);
    if (const auto breakStmt = stmt->asBreak()) return visitBreakStmt(breakStmt);
    if (stmt->asContinue()) return visitContinueStmt();
    assert(0);
}

void LgsCodeGen::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    assert(stmtsBlock);
    for (const auto stmt : stmtsBlock->stmts) {
        visitStmt(stmt);
    }
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
    if (stack.inCoroutine()) yield();
    loop->incAndJumpToCond(cg);
    cg.startBlock(loop->IRExitBlock);
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
    cg.startBlock(loop->IRCondBlock);
    loop->iValue = loop->loadIndex(cg);
    const auto loopEnd = cg.builder.CreateSExt(loop->loopEnd(cg), cg.sizeTy());
    const auto condition = cg.builder.CreateICmpSLT(loop->iValue, loopEnd);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock);
    if (!loop->loopVars.empty()) {
        loop->loopVars[0]->IRValue = loop->iValue;
    }
}

void LgsCodeGen::visitForeachLoop(LgsForeachLoop* loop) {
    visitExpr(loop->iterExpr);
    loop->iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    cg.builder.CreateStore(cg.sizeZero(), loop->iPtr);
    const auto loopEnd = cg.builder.CreateSExt(loop->loopEnd(cg), cg.sizeTy());
    cg.branchAndStartBlock(loop->IRCondBlock);

    loop->iValue = loop->loadIndex(cg);
    const auto condition = cg.builder.CreateICmpSLT(loop->iValue, loopEnd);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
    cg.startBlock(loop->IRBodyBlock);

    const auto iterable = loop->iterExpr->type->asIterable();
    iterable->unpackLoopIR(cg, loop);
}

void LgsCodeGen::visitInfiniteLoop(const LgsInfiniteLoop* loop) const {
    cg.branchAndStartBlock(loop->IRBodyBlock);
}

void LgsCodeGen::visitLoopMetaVar(LgsLoopMetaVar* metaVar) const {
    const auto loop = metaVar->forLoop;
    const auto iValue = loop->iValue;
    switch (metaVar->varType) {
    case FOR_I: {
        metaVar->IRValue = iValue;
        break;
    }
    case FOR_IS_FIRST: {
        const auto loopStart = cg.builder.CreateSExt(loop->loopStart(cg), cg.sizeTy());
        metaVar->IRValue = cg.builder.CreateICmpEQ(iValue, loopStart);
        break;
    }
    case FOR_IS_LAST: {
        const auto loopEnd = cg.builder.CreateSExt(loop->loopEnd(cg), cg.sizeTy());
        const auto decremented = cg.builder.CreateSub(loopEnd, cg.usize(1));
        metaVar->IRValue = cg.builder.CreateICmpEQ(iValue, decremented);
        break;
    }
    case FOR_ELEMENT:
        break;
    }
}

void LgsCodeGen::visitWhileLoop(const LgsWhileLoop* loop) {
    cg.builder.CreateBr(loop->IRCondBlock);
    // Condition
    cg.startBlock(loop->IRCondBlock);
    const auto condition = getIRValue(loop->condExpr);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
    // Body
    cg.startBlock(loop->IRBodyBlock);
}

void LgsCodeGen::visitVarDec(LgsVarDec* varDec) {
    if (varDec->shouldAllocate()) {
        varDec->IRValue = cg.builder.CreateAlloca(varDec->type->getIRType(cg));
        varDec->expr->destPtrValue = varDec->IRValue;
        visitExpr(varDec->expr, true);
        if (varDec->expr->IRValue != varDec->IRValue) {
            cg.builder.CreateStore(varDec->expr->IRValue, varDec->IRValue);
        }
    } else {
        visitExpr(varDec->expr, true);
        varDec->IRValue = varDec->expr->IRValue;
    }
    assert(varDec->IRValue);
    varDec->IRValue->setName(varDec->name);
}

void LgsCodeGen::visitAssignment(const LgsAssignment* assignment) {
    const auto lValue = assignment->lValue;
    const auto rValue = assignment->rValue;
    if (const auto iterIndex = lValue->asIterIndex()) {
        visitIterIndex(iterIndex, true);
    } else if (const auto var = lValue->asVariable()) {
        visitVariable(var);
    } else if (const auto selection = lValue->asSelection()) {
        visitSelection(selection);
    } else {
        assert(0);
    }
    assignment->rValue->destPtrValue = lValue->IRValue;
    visitExpr(assignment->rValue, true);

    Value* results = nullptr;
    switch (assignment->assignmentType) {
    case ASSIGN: lValue->assign(cg, rValue); return;
    case ASSIGN_ADD: results = lValue->type->addIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_SUB: results = lValue->type->subIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_MUL: results = lValue->type->mulIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_DIV: results = lValue->type->divIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_MOD: results = lValue->type->modIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_AND: results = lValue->type->bitAndIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_OR: results = lValue->type->bitOrIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_XOR: results = lValue->type->bitXorIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_LSHIFT: results = lValue->type->lshiftIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    case ASSIGN_RSHIFT: results = lValue->type->rshiftIR(cg, lValue->loadIR(cg), rValue->loadIR(cg)); break;
    }
    assert(results);
    cg.builder.CreateStore(results, lValue->IRValue);
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
    visitExpr(ifStmt->ifCond);
    cg.builder.CreateCondBr(ifStmt->ifCond->IRValue, IRBlockIfTrue, ifStmt->IRExitBlock);
    cg.startBlock(IRBlockIfTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock);
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
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    // else block
    stack.enterScope(ifStmt);
    cg.startBlock(IRBlockElse);
    visitStmtsBlock(ifStmt->elseBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock);
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
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchIfNeeded(ifStmt->IRExitBlock);
    stack.exitScope();

    for (int i = 0; i < ifStmt->elseIfs.size(); ++i) {
        const auto [expr, stmtBlock] = ifStmt->elseIfs[i];
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockElseIfCheck);
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
        cg.startBlock(IRBlockTrue);
        visitStmtsBlock(stmtBlock);
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }

    if (ifStmt->elseBlock) {
        stack.enterScope(ifStmt);
        cg.startBlock(IRBlockElse);
        visitStmtsBlock(ifStmt->elseBlock);
        cg.branchIfNeeded(ifStmt->IRExitBlock);
        stack.exitScope();
    }
    cg.startBlock(ifStmt->IRExitBlock);
}

void LgsCodeGen::visitSwitch(LgsSwitch* pm) {
    assert(pm->cond);
    const auto defaultBlock = cg.createBlock(BLOCK_NAME_ELSE);
    const auto exitBlock = cg.createBlock(BLOCK_NAME_EXIT_PATTERN);
    visitExpr(pm->cond);
    const auto exprIRValue = pm->cond->hash(cg);
    SwitchInst* switchInst;
    if (pm->elseBlock) {
        const auto numOfCases = pm->patterns.size() + !!pm->elseBlock;
        switchInst = cg.builder.CreateSwitch(exprIRValue, defaultBlock, numOfCases);
    } else {
        switchInst = cg.builder.CreateSwitch(exprIRValue, exitBlock, pm->patterns.size());
    }

    std::vector<BasicBlock*> blocks;
    for (size_t i = 0; i < pm->patterns.size(); ++i) {
        stack.enterScope(pm);
        const auto [expr, stmtsBlock] = pm->patterns[i];
        visitExpr(expr);
        const auto patterIRValue = expr->hash(cg);
        const auto patternBlock = cg.createBlock(BLOCK_NAME_CASE_PREFIX + std::to_string(i), currentIRFunc);
        switchInst->addCase(dyn_cast<ConstantInt>(patterIRValue), patternBlock);
        cg.startBlock(patternBlock);
        visitStmtsBlock(stmtsBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    if (pm->elseBlock) {
        stack.enterScope(pm);
        cg.startBlock(defaultBlock);
        visitStmtsBlock(pm->elseBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }
    cg.startBlock(exitBlock);
}

void LgsCodeGen::visitContinueStmt() {
    stack.currentLoop()->incAndJumpToCond(cg);
}

void LgsCodeGen::visitReturnStmt(LgsReturn* returnStmt) {
    visitExpr(returnStmt->expr);
    returnStmt->IRValue = returnStmt->expr ? returnStmt->expr->IRValue : nullptr;
    const auto currentFunc = stack.currentFunc();
    if (currentFunc->needsCleanup()) {
        returnStmt->parentBlock = cg.builder.GetInsertBlock();
        const auto cleanupBlock = currentFunc->getCleanupBlock(cg);
        cg.builder.CreateBr(cleanupBlock);
    } else {
        cg.callPopStack(currentFunc->hasDefers, currentFunc->needsCleanup());
        if (currentFunc->funcType->rt->isVoid()) {
            cg.builder.CreateRetVoid();
        } else {
            cg.builder.CreateRet(getIRValue(returnStmt));
        }
    }
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

void LgsCodeGen::visitCoroutine(const LgsCoroutine* coroutine) {
    const LgsFuncCall* fc = nullptr;
    if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
        fc = coroutine->funcCall;
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
        fc = coroutine->selection->asMethodCall();
    }
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.callLgsFunc("stack_addCoro", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {func, ctx});
}

void LgsCodeGen::visitDeferStmt(const LgsDeferStmt* deferStmt) {
    const LgsFuncCall* fc = nullptr;
    if (deferStmt->funcCall) {
        visitFuncCall(deferStmt->funcCall);
        fc = deferStmt->funcCall;
    } else if (deferStmt->selection) {
        visitSelection(deferStmt->selection);
        fc = deferStmt->selection->asMethodCall();
    }
    for (const auto& arg : fc->args) {
        visitExpr(arg);
    }
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.callLgsFunc("stack_addDefer", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {func, ctx});
}

void LgsCodeGen::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitExpr(ioStmt->varDec->expr);
    visitStmtsBlock(ioStmt->stmtsBlock);
}

void LgsCodeGen::visitExpr(LgsExpr* expr, const bool assign) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        visitExpr(iter->size);
    }
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        visitTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        if (checkMock(expr)) return;
        if (const auto func = expr->asFunc()) return visitLambda(func);
        if (const auto instance = expr->asInstance()) return visitInstance(instance);
        if (const auto funcCall = expr->asFuncCall()) return visitFuncCall(funcCall);
        if (const auto strConst = expr->asStrConst()) return visitStrConst(strConst);
        if (const auto selection = expr->asSelection()) return visitSelection(selection, assign);
        if (const auto arrayExpr = expr->asArrayExpr()) return visitArrayExpr(arrayExpr);
        if (const auto hashMap = expr->asHashMap()) return visitHashMap(hashMap);
        if (const auto iterIndex = expr->asIterIndex()) return visitIterIndex(iterIndex, assign);
        if (const auto variable = expr->asVariable()) return visitVariable(variable);
        if (const auto postfixExpr = expr->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
        if (const auto prefixExpr = expr->asPrefixExpr()) return visitPrefixExpr(prefixExpr);
        if (const auto vecExpr = expr->asVectorExpr()) return visitVectorExpr(vecExpr);
        if (const auto intConst = expr->asIntConst()) return visitIntConst(intConst);
        if (const auto floatConst = expr->asFloatConst()) return visitFloatConst(floatConst);
        if (const auto loopMetaVar = expr->asLoopMetaVar()) return visitLoopMetaVar(loopMetaVar);
        if (const auto null = expr->asNull()) return visitNull(null);
        if (const auto cast = expr->asCast()) return visitCast(cast);
        if (const auto json = expr->asJson()) return visitJson(json);
        if (expr->asTypeExpr()) return;
        assert(0);
    }
}

void LgsCodeGen::visitBinaryExpr(LgsBinaryExpr* binExpr) {
    const auto l = binExpr->left;
    const auto r = binExpr->right;
    visitExpr(l);
    visitExpr(r);
    const auto selfLoad = l->loadIR(cg);
    const auto otherLoad = r->loadIR(cg);
    const auto ltype = l->type;
    switch (binExpr->op.opType) {
    case ADD:
        binExpr->IRValue = ltype->addIR(cg, selfLoad, otherLoad); break;
    case SUB:
        binExpr->IRValue = ltype->subIR(cg, selfLoad, otherLoad); break;
    case MUL:
        binExpr->IRValue = ltype->mulIR(cg, selfLoad, otherLoad); break;
    case DIV:
        binExpr->IRValue = ltype->divIR(cg, selfLoad, otherLoad); break;
    case MODULO:
        binExpr->IRValue = ltype->modIR(cg, selfLoad, otherLoad); break;
    case BIT_AND:
        binExpr->IRValue = ltype->bitAndIR(cg, selfLoad, otherLoad); break;
    case BIT_OR:
        binExpr->IRValue = ltype->bitOrIR(cg, selfLoad, otherLoad); break;
    case BIT_XOR:
        binExpr->IRValue = ltype->bitXorIR(cg, selfLoad, otherLoad); break;
    case LSHIFT:
        binExpr->IRValue = ltype->rshiftIR(cg, selfLoad, otherLoad); break;
    case RSHIFT:
        binExpr->IRValue = ltype->lshiftIR(cg, selfLoad, otherLoad); break;
    case EQ:
        binExpr->IRValue = ltype->eqIR(cg, selfLoad, otherLoad); break;
    case NE:
        binExpr->IRValue = ltype->neIR(cg, selfLoad, otherLoad); break;
    case LT:
        binExpr->IRValue = ltype->ltIR(cg, selfLoad, otherLoad); break;
    case GT:
        binExpr->IRValue = ltype->gtIR(cg, selfLoad, otherLoad); break;
    case GE:
        binExpr->IRValue = ltype->geIR(cg, selfLoad, otherLoad); break;
    case LE:
        binExpr->IRValue = ltype->leIR(cg, selfLoad, otherLoad); break;
    case AND:
        binExpr->IRValue = ltype->andIR(cg, selfLoad, otherLoad); break;
    case OR:
        binExpr->IRValue = ltype->orIR(cg, selfLoad, otherLoad); break;
    case IN:
        binExpr->IRValue = r->type->asIterable()->inIR(cg, r, l); break;
    case NOOP: assert(0);
    }
}

void LgsCodeGen::visitTernaryExpr(LgsTernaryExpr* ternaryExpr) {
    const auto cond = ternaryExpr->condExpr;
    const auto then = ternaryExpr->thenExpr;
    const auto else_ = ternaryExpr->elseExpr;
    visitExpr(cond);
    visitExpr(then);
    visitExpr(else_);
    ternaryExpr->IRValue = cg.builder.CreateSelect(cond->IRValue, then->IRValue, else_->IRValue);
}

void LgsCodeGen::visitCast(LgsCast* cast) {
    assert(cast->value);
    visitExpr(cast->value);
    cast->IRValue = cast->value->IRValue;
}

void LgsCodeGen::visitLambda(LgsFunc* func) {
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = currentIRFunc;
    const auto lambdaID = namesCounter.fetch_add(1);
    func->funcType->IRName = LGS_ANONYMOUS_STR + std::to_string(lambdaID);
    func->IRValue = func->getIRFunc(cg);
    visitFunc(func);
    currentIRFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
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
    } else if (intConst->type->asSize()) {
        intConst->IRValue = cg.usize(intConst->value);
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
    if (array->destPtrValue) {
        array->IRValue = array->destPtrValue;
    }
    if (array->type->asSArray()) {
        setStaticArray(array);
    } else if (array->type->asDArray()) {
        setDynamicArray(array);
    } else if (array->type->asSet()) {
        setSetExpr(array);
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitHashMap(LgsHashMap* hashMap) {
    const auto map = hashMap->type->asMap();
    const auto valueType = map->typePair->value;
    const auto elementSize = cg.usize(valueType->getSizeBytes());
    hashMap->IRValue = cg.callMalloc(map->getSizeBytes(), hashMap->owner, hashMap->type->getRTType());
    LgsFunc initFunc("init", &LGS_VOID, {map, &LGS_LONG}, BUILTIN | METHOD);
    initFunc.callIR(cg, {getIRValue(hashMap), elementSize});
    for (const auto [key, value] : hashMap->pairs) {
        visitExpr(key);
        visitExpr(value);
        map->getAddFunc()->callIR(cg, {hashMap->IRValue, key->IRValue, value->IRValue});
    }
}

void LgsCodeGen::visitVectorExpr(LgsVectorExpr* vectorExpr) {
    const auto ty = vectorExpr->type->getIRType(cg);
    if (vectorExpr->destPtrValue) {
        vectorExpr->IRValue = vectorExpr->destPtrValue;
    } else {
        vectorExpr->IRValue = cg.builder.CreateAlloca(ty);
    }
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
        variable->IRValue = variable->ref.varDec->IRValue;
        break;
    case PARAM:
        variable->IRValue = variable->ref.param->IRValue;
        break;
    case FUNC:
        variable->IRValue = variable->ref.func->getIRFunc(cg);
        break;
    case OBJECT:
        variable->IRValue = getIRValue(variable->ref.object->singleton);
        break;
    case ENUM:
    case FIELD:
        if (variable->ref.field->type->asEnum()) {
            variable->IRValue = cg.getIRStr(variable->name);
        } else {
            variable->IRValue = variable->ref.field->IRValue;
        }
        break;
    case GENERIC:
        assert(0);
    case INTERFACE:
    case SUBTYPE:
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCodeGen::visitSelection(LgsSelection* selection, const bool assign) {
    visitExpr(selection->exprs.front());
    for (int i = 0; i < selection->exprs.size() - 1; ++i) {
        const auto parent = selection->exprs[i];
        const auto child = selection->exprs[i + 1];
        if (const auto var = child->asVariable()) {
            visitFieldSelection(var, parent);
        } else if (const auto methodCall = child->asFuncCall()) {
            const bool isTest = stack.currentFunc()->isTest && parent->type->getName() == LgsTest::name && methodCall->name == "mock";
            if (isTest) continue;
            visitFuncCall(methodCall);
        } else if (const auto iterIndex = child->asIterIndex()) {
            const auto baseExpr = iterIndex->getBaseExpr()->asVariable();
            const auto field = parent->type->getField(baseExpr->name);
            field->parentIRValue = parent->IRValue;
            field->parentIRType = parent->type->getIRType(cg);
            visitField(field);
            iterIndex->destPtrValue = field->IRValue;
            visitIterIndex(iterIndex, false);
        } else {
            assert(0);
        }
    }
    selection->IRValue = selection->lastExpr()->IRValue;
    if (assign && selection->type->asNullable()) {
        setNullableValue(selection);
    }
}

void LgsCodeGen::visitFieldSelection(LgsVariable* var, LgsExpr* parent) const {
    if (var->ref.symbolType == FUNC) {
        var->IRValue = var->ref.func->getIRFunc(cg);
        return;
    }
    const auto field = parent->type->getField(var->name);
    if (parent->asTypeExpr()) {
        const auto object = parent->type->asObject();
        if (object && object->singleton) {
            field->parentIRValue = object->singleton->IRValue;
            field->parentIRType = object->getIRType(cg);
            visitField(field);
            var->IRValue = field->IRValue;
            return;
        }
    }
    field->parentIRValue = parent->IRValue;
    field->parentIRType = parent->type->getIRType(cg);
    visitField(field);
    if (field->type->asObject()) {
        var->IRValue = cg.builder.CreateLoad(cg.ptrTy(), field->IRValue);
    } else {
        var->IRValue = field->IRValue;
    }
}

void LgsCodeGen::visitFuncCall(LgsFuncCall* funcCall) {
    for (int i = 0; i < funcCall->args.size(); ++i) {
        visitExpr(funcCall->args[i]);
    }

    if (funcCall->ref.symbolType == PARAM) {
        LgsFunc f(funcCall->ref.param->type->asFuncType());
        f.IRValue = getIRValue(funcCall->ref.param);
        if (!funcCall->isCoroutine && !funcCall->isDeferred) {
            funcCall->IRValue = f.call(cg, funcCall->args);
        }
        return;
    }

    if (funcCall->ref.symbolType == VAR_DEC) {
        LgsFunc f(funcCall->ref.varDec->type->asFuncType());
        f.IRValue = getIRValue(funcCall->ref.varDec);
        if (!funcCall->isCoroutine && !funcCall->isDeferred) {
            funcCall->IRValue = f.call(cg, funcCall->args);
        }
        return;
    }

    auto ft = funcCall->func->funcType;
    if (ft->hasDefaults()) {
        const auto diff = ft->params.size() - funcCall->args.size() - 1;
        for (int i = diff; i < ft->params.size(); ++i) {
            visitExpr(ft->params[i].expr);
        }
    }

    if (ft->isVirtual) {
        const auto self = funcCall->selfPtr;
        const auto keyIR = cg.getIRStr(ft->name);
        funcCall->func->IRValue = cg.callGetFromVTable(self->IRValue, keyIR);
    } else {
        visitIterFunc(funcCall);
    }

    if (!funcCall->isCoroutine && !funcCall->isDeferred) {
        funcCall->IRValue = funcCall->func->call(cg, funcCall->args);
    }
}

void LgsCodeGen::visitIterFunc(const LgsFuncCall* funcCall) {
    if (funcCall->name == MAP_FUNC_NAME) {
        createMapFunc(funcCall->func);
    } else if (funcCall->name == FILTER_FUNC_NAME) {
        createFilterFunc(funcCall->func);
    } else if (funcCall->name == FOREACH_FUNC_NAME) {
        assert(0);
    }
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
        auto d = cg.builder.CreateSIToFP(exprIRVal, cg.doubleTy());
        prefixExpr->IRValue = cg.callFunc("sqrt", cg.doubleTy(), {cg.doubleTy()}, {d});
        break;
    }
    }
}

void LgsCodeGen::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto baseExpr = postfixExpr->baseExpr;
    visitExpr(baseExpr);
    postfixExpr->IRValue = postfixExpr->baseExpr->loadIR(cg);
    assert(baseExpr->IRValue->getType()->isPointerTy());
    const auto baseExprType = postfixExpr->baseExpr->type->getIRType(cg);
    const auto one = ConstantInt::get(baseExprType, 1, true);
    Value* newValue = nullptr;
    switch (postfixExpr->op) {
    case INC: {
        newValue = cg.builder.CreateAdd(postfixExpr->IRValue, one);
        break;
    }
    case DEC: {
        newValue = cg.builder.CreateSub(postfixExpr->IRValue, one);
        break;
    }
    }
    cg.builder.CreateStore(newValue, postfixExpr->baseExpr->IRValue);
}

void LgsCodeGen::visitStrConst(LgsStrConst* strConst) {
    if (strConst->parts.empty()) {
        strConst->IRValue = cg.getIRStr(strConst->value);
    } else {
        for (const auto parts : strConst->parts) {
            visitExpr(parts);
        }
        auto formatted = strConst->formatedStr;
        std::vector<Value*> values;
        for (const auto part : strConst->parts) {
            auto partIR = part->IRValue;
            values.push_back(partIR);
            const auto pos = formatted.find(LGS_STR_FMT_PLACEHOLDER);
            if (pos != std::string::npos) {
                formatted.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), part->type->strFormatPart());
            }
        }
        const auto arrTyp = ArrayType::get(cg.i8Ty(), 1024);
        const auto buffer = cg.builder.CreateAlloca(arrTyp);
        strConst->IRValue = buffer;
        std::vector IRArgs = {strConst->IRValue, cg.getIRStr(formatted + "\n")};
        IRArgs.insert(IRArgs.end(), values.begin(), values.end());
        // cg.callSprintf(IRArgs);
    }
}

void LgsCodeGen::visitInstance(LgsInstance* instance) {
    if (instance->IRValue) return;
    const auto obj = instance->obj;
    instance->IRValue = cg.callMalloc(obj->getSizeBytes(), instance->owner, obj->getRTType());

    std::unordered_set<std::string> visited;
    for (const auto& [argName, arg] : instance->args) {
        visited.insert(argName);
        const auto exprIR = getIRValue(arg);
        const auto field = instance->obj->getField(argName);
        arg->destPtrValue = field->IRValue;
        field->parentIRValue = instance->IRValue;
        field->parentIRType = instance->obj->getIRType(cg);
        visitField(field);
        visitExpr(field->expr);
        cg.builder.CreateStore(exprIR, field->IRValue);
    }

    // Zero values
    for (const auto field : instance->obj->fields) {
        if (visited.count(field->name) || field->type->asEnum()) continue;
        field->parentIRValue = instance->IRValue;
        field->parentIRType = instance->obj->getIRType(cg);
        if (!field->expr) {
            field->expr = field->type->getZeroValue();
            field->expr->destPtrValue = field->IRValue;
            if (field->isOwner && field->type->isHeapAlloc) {
                field->expr->owner = field;
            }
        }
        visitField(field);
        visitExpr(field->expr, true);
        if (field->expr->IRValue == field->IRValue) continue;
        cg.builder.CreateStore(field->expr->IRValue, field->IRValue);
    }
    if (obj->implements.empty()) return;
    resolveVirtuals(instance);
}

void LgsCodeGen::visitIterIndex(LgsIterIndex* iterIndex, const bool assign) {
    assert(!iterIndex->index.to);
    if (iterIndex->baseExpr->type->asSArray()) {
        visitExpr(iterIndex->index.from);
        visitExpr(iterIndex->index.to);
        iterIndex->setIRElementPtr(cg, assign);
    } else {
        visitExpr(iterIndex->baseExpr);
        visitExpr(iterIndex->index.from);
        visitExpr(iterIndex->index.to);
        iterIndex->setIRElementPtr(cg, assign);
    }
}

void LgsCodeGen::visitNull(LgsNull* null) const {
    null->IRValue = cg.null();
}

void LgsCodeGen::visitJson(LgsJson* json) {
    if (const auto instance = json->instance) {
        json->instance->destPtrValue = json->destPtrValue;
        instance->obj->getIRType(cg);
    } else if (const auto arr = json->arr) {
        json->arr->destPtrValue = json->destPtrValue;
        visitArrayExpr(arr);
        json->IRValue = arr->IRValue;
    } else if (const auto strConst = json->strConst) {
        json->strConst->destPtrValue = json->destPtrValue;
        visitStrConst(strConst);
        json->IRValue = strConst->IRValue;
    } else if (const auto intConst = json->intConst) {
        json->intConst->destPtrValue = json->destPtrValue;
        visitIntConst(intConst);
        json->IRValue = intConst->IRValue;
    } else if (const auto floatConst = json->floatConst) {
        json->floatConst->destPtrValue = json->destPtrValue;
        visitFloatConst(floatConst);
        json->IRValue = floatConst->IRValue;
    } else if (const auto null = json->null) {
        json->null->destPtrValue = json->destPtrValue;
        null->IRValue = cg.null();
        json->IRValue = null->IRValue;
    }
}

void LgsCodeGen::setNullableValue(LgsExpr* expr) {
    if (const auto var = expr->asVariable()) {
        visitVariable(var);
    }
    // const auto nullable = expr->type->asNullable();
    // const auto ty = nullable->baseType->getIRType(cg);
    // expr->IRValue = cg.builder.CreateLoad(ty, nullable->valueField);
}

void LgsCodeGen::resolveVirtuals(const LgsInstance* instance) const {
    const auto obj = instance->obj;
    for (const auto& field : obj->fields) {
        if (!field->isVirtual) continue;
        const auto keyIRStr = cg.getIRStr(field->name);
        const auto objIR = obj->getIRType(cg);
        const auto fieldGEP = cg.builder.CreateStructGEP(objIR, instance->IRValue, field->position);
        cg.callAddToVTable(instance->IRValue, keyIRStr, fieldGEP);
    }

    // Implemented interface methods
    for (const auto implement : instance->obj->implements) {
        for (const auto& [name, interfaceMethod] : implement->methods) {
            if (!interfaceMethod->stmtsBlock) continue;
            const auto objMethod = obj->methods.find(name);
            if (objMethod != obj->methods.end()) continue;
            const auto keyIRStr = cg.getIRStr(interfaceMethod->funcType->name);
            const auto IRFunc = interfaceMethod->getIRFunc(cg);
            cg.callAddToVTable(instance->IRValue, keyIRStr, IRFunc);
        }
    }

    for (const auto& [methodName, method] : obj->methods) {
        if (!method->funcType->isVirtual) continue;
        const auto keyIRStr = cg.getIRStr(method->funcType->name);
        const auto IRFunc = method->getIRFunc(cg);
        cg.callAddToVTable(instance->IRValue, keyIRStr, IRFunc);
    }
}

bool LgsCodeGen::checkMock(LgsExpr* expr) {
    const auto currentFunc = stack.currentFunc();
    if (currentFunc->isTest) {
        for (auto [when, then] : currentFunc->mocks) {
            if (!when->equals(expr)) continue;
            expr->IRValue = then->IRValue;
            return true;
        }
    }
    return false;
}

void LgsCodeGen::yield() const {
    const auto doYieldBlock = cg.createBlock("do_yield_block");
    const auto continueBlock = cg.createBlock("continue_block");
    const auto shouldYield = cg.callLgsFunc("scheduler_shouldYield", cg.i1Ty());
    cg.builder.CreateCondBr(shouldYield, doYieldBlock, continueBlock);
    cg.startBlock(doYieldBlock);
    cg.callLgsFunc("scheduler_yield", cg.voidTy());
    cg.branchAndStartBlock(continueBlock);
}

void LgsCodeGen::createPrologue(LgsFunc* func) {
    if (func->isTest) for (auto [_, then] : func->mocks) visitExpr(then);
    currentIRFunc = func->getIRFunc(cg);
    const auto entryBlock = cg.createBlock(BLOCK_NAME_ENTRY, currentIRFunc);
    cg.builder.SetInsertPoint(entryBlock);
    if (func->funcType->name == LGS_MAIN_FUNC_NAME) {
        cg.callLgsFunc("runtime_init", cg.voidTy());
    }
    cg.callStackPush(func->hasDefers, func->needsCleanup());
}

void LgsCodeGen::createEpilogue(LgsFunc* func) {
    const auto needsCleanup = func->needsCleanup();
    if (!func->hasDefers && !needsCleanup) {
        cg.callPopStack(false, false);
        return;
    }
    cg.branchAndStartBlock(func->getCleanupBlock(cg));
    if (func->hasDefers) cg.callLgsFunc("stack_callDefers", cg.voidTy());
    currentIRFunc = nullptr;

    if (needsCleanup) {
        if (func->returnStmts.empty()) {
            cg.callPopStack(func->hasDefers, func->needsCleanup());
        } else if (func->returnStmts.size() == 1) {
            if (func->owners.size() == 1) {
                const auto returnRef = func->returnStmts.front()->expr;
                const auto heapExprRef = func->owners.front();
                if (returnRef->equals(heapExprRef)) {
                    cg.callPopStack(func->hasDefers, func->needsCleanup());
                    cg.builder.CreateRet(getIRValue(func->returnStmts.front()));
                    return;
                }
            }
            cg.callPopStack(func->hasDefers, func->needsCleanup());
            cg.builder.CreateRet(getIRValue(func->returnStmts.front()));
        } else {
            PHINode *phi = nullptr;
            if (!func->funcType->rt->isVoid()) {
                phi = cg.builder.CreatePHI(cg.ptrTy(), func->returnStmts.size());
            }
            for (const auto stmt : func->returnStmts) {
                const auto retVal = getIRValue(stmt);
                if (phi) {
                    phi->addIncoming(retVal, stmt->parentBlock);
                }
            }
            cg.callPopStack(func->hasDefers, func->needsCleanup());
            cg.builder.CreateRet(phi);
        }
    } else {
        cg.callPopStack(func->hasDefers, needsCleanup);
    }
}

void LgsCodeGen::initMainArgs(const LgsMainFunc* mainFunc) {
    if (mainFunc->funcType->params.empty()) return;
    const auto& args = mainFunc->args;
    const auto dArray = args->type->asDArray();
    dArray->size->IRValue = currentIRFunc->getArg(0);
    setDynamicArray(args);
    const auto argv = currentIRFunc->getArg(1);
    const auto cond = cg.builder.CreateSub(dArray->size->IRValue, cg.i32(1));
    cg.loop(cond, [this, &args, &dArray, &argv](Value* iValue, BasicBlock*) {
        const auto i = cg.builder.CreateAdd(iValue, cg.usize(1));
        const auto gep = cg.builder.CreateInBoundsGEP(cg.ptrTy(), argv, {cg.i32Zero(), i});
        dArray->getAddFunc()->callIR(cg, {args->IRValue, cg.builder.CreateLoad(cg.ptrTy(), gep)});
    });
    mainFunc->funcType->params[0].IRValue = args->IRValue;
}

Value* LgsCodeGen::getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const {
    if (fc->args.empty()) return cg.null();
    const auto ctx = cg.builder.CreateAlloca(ctxTy);
    for (int i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i]->IRValue;
        const auto fieldPtr = cg.builder.CreateStructGEP(dyn_cast<StructType>(ctxTy), ctx, i);
        cg.builder.CreateStore(v, fieldPtr);
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
    func = cg.getFunc(fc->name + "_thunk", ft, Function::PrivateLinkage);
    const auto entryBlock = BasicBlock::Create(cg.context, BLOCK_NAME_ENTRY);
    entryBlock->insertInto(func);
    cg.builder.SetInsertPoint(entryBlock);

    std::vector<Value*> args;
    for (int i = 0; i < fc->args.size(); i++) {
        const auto gep = cg.builder.CreateStructGEP(ctxTy, func->arg_begin(), i);
        const auto v = cg.builder.CreateLoad(ctxTy->getStructElementType(i), gep);
        args.push_back(v);
    }

    const auto deferFunc = fc->func->getIRFunc(cg);
    cg.builder.CreateCall(deferFunc, args);
    cg.builder.CreateRetVoid();

    cg.builder.restoreIP(cg.savedIP);
    return func;
}

void LgsCodeGen::setStaticArray(LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asSArray();
    const auto arrTypeIR = arr->getIRType(cg);
    if (!arrayExpr->destPtrValue) {
        arrayExpr->IRValue = cg.builder.CreateAlloca(arrTypeIR);
    }
    if (arrayExpr->elements.empty()) {
        const auto size = cg.builder.CreateMul(arr->size->IRValue, cg.i32(arr->baseType->getSizeBytes()));
        cg.builder.CreateMemSet(arrayExpr->IRValue, cg.i8(0), size, MaybeAlign());
        return;
    }
    if (arr->baseType->asIterable()) {
        setNestedSArr(arrayExpr, arrTypeIR, arrayExpr->IRValue, {cg.i32Zero()});
    } else {
        for (int i = 0; i < arrayExpr->elements.size(); ++i) {
            const auto element = arrayExpr->elements[i];
            element->destPtrValue = arrayExpr->IRValue;
            visitExpr(element);
            const auto gep = cg.builder.CreateInBoundsGEP(arrTypeIR, arrayExpr->IRValue, {cg.i32(i)});
            cg.builder.CreateStore(element->IRValue, gep);
        }
    }
}

void LgsCodeGen::setNestedSArr(const LgsArrayExpr* arrayExpr, Type* parentType, Value* parentValue, const std::vector<Value*>& indices) {
    for (int i = 0; i < arrayExpr->elements.size(); ++i) {
        const auto element = arrayExpr->elements[i];
        element->destPtrValue = arrayExpr->IRValue;
        if (const auto innerArrExpr = element->asArrayExpr()) {
            auto innerArrIndices = indices;
            innerArrIndices.push_back(cg.i32(i));
            setNestedSArr(innerArrExpr, parentType, parentValue, innerArrIndices);
        } else {
            auto elementIndices = indices;
            elementIndices.push_back(cg.i32(i));
            visitExpr(element);
            const auto gep = cg.builder.CreateGEP(parentType, parentValue, elementIndices);
            cg.builder.CreateStore(element->IRValue, gep);
        }
    }
}

void LgsCodeGen::setDynamicArray(LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asDArray();
    const auto size = arr->baseType->getSizeBytes();
    if (!arrayExpr->IRValue) {
        const auto rtt = arr->baseType->getRTType();
        arrayExpr->IRValue = cg.callLgsFunc("darray_init", cg.ptrTy(), {cg.sizeTy(), cg.sizeTy()}, {cg.i64(size), cg.usize(rtt)});
        cg.addHeap(arrayExpr->owner, rtt, arrayExpr->IRValue);
    }
    for (int i = 0; i < arrayExpr->elements.size(); ++i) {
        const auto element = arrayExpr->elements[i];
        element->destPtrValue = arrayExpr->IRValue;
        visitExpr(element);
        arr->getAddFunc()->call(cg, {arrayExpr, element});
    }
}

void LgsCodeGen::setSetExpr(LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asSet();
    const auto size = arr->baseType->getSizeBytes();
    arrayExpr->IRValue = cg.callMalloc(arr->getSizeBytes(), arrayExpr->owner, arr->getRTType());
    LgsFunc initFunc("init", &LGS_VOID, {arr, &LGS_SIZE, &LGS_SIZE}, BUILTIN | METHOD);
    initFunc.callIR(cg, {arrayExpr->IRValue, cg.i64(size), cg.usize(arr->baseType->getRTType())});

    for (int i = 0; i < arrayExpr->elements.size(); ++i) {
        const auto element = arrayExpr->elements[i];
        element->destPtrValue = arrayExpr->IRValue;
        visitExpr(element);
        arr->getAddFunc()->call(cg, {arrayExpr, element});
    }
}

void LgsCodeGen::createMapFunc(LgsFunc* func) {
    if (cg.IRModule->getFunction(func->getIRName())) return;
    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = currentIRFunc;

    // Init
    currentIRFunc = func->getIRFunc(cg);
    const auto& originalArr = func->funcType->params[0];
    const auto& callback = func->funcType->params[1];
    const auto entryBlock = cg.createBlock(BLOCK_NAME_ENTRY, currentIRFunc);
    const auto condBlock = cg.createBlock();
    const auto bodyBlock = cg.createBlock();
    const auto exitBlock = cg.createBlock();
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush(func->hasDefers, func->needsCleanup());

    const auto dArray = originalArr.type->asDArray();
    LgsArrayExpr newArr(dArray);
    visitArrayExpr(&newArr);

    const auto iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    const auto loopStart = cg.builder.CreateSExt(cg.sizeZero(), cg.sizeTy());
    cg.builder.CreateStore(loopStart, iPtr);
    cg.builder.CreateBr(condBlock);

    // Condition
    cg.startBlock(condBlock);
    const auto iValue = cg.builder.CreateLoad(cg.sizeTy(), iPtr);
    const auto condition = cg.builder.CreateICmpSLT(iValue, dArray->lengthIR(cg, func->funcType->params[0].IRValue));
    cg.builder.CreateCondBr(condition, bodyBlock, exitBlock);

    // Body
    cg.startBlock(bodyBlock);
    const auto element = dArray->getIRElement(cg, originalArr.IRValue, iValue);
    const auto ft = dyn_cast<FunctionType>(callback.type->getIRType(cg));
    const auto arg = cg.builder.CreateLoad(dArray->baseType->getIRType(cg), element);
    const auto v = cg.builder.CreateCall(ft, callback.IRValue, {arg});
    dArray->getAddFunc()->callIR(cg, {newArr.IRValue, cg.getPtrTo(v)});

    // Increment
    const auto inc = cg.builder.CreateAdd(iValue, cg.usize(1));
    cg.builder.CreateStore(inc, iPtr);
    cg.builder.CreateBr(condBlock);

    // End func
    cg.startBlock(exitBlock);
    cg.callPopStack(func->hasDefers, func->needsCleanup());
    cg.builder.CreateRet(newArr.IRValue);

    // Restore state
    currentIRFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    func->IRValue = func->getIRFunc(cg);
}

void LgsCodeGen::createFilterFunc(LgsFunc* func) {
    if (cg.IRModule->getFunction(func->getIRName())) return;
    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = currentIRFunc;

    // Init
    currentIRFunc = func->getIRFunc(cg);
    const auto& originalArr = func->funcType->params[0];
    const auto& callback = func->funcType->params[1];
    const auto entryBlock = cg.createBlock(BLOCK_NAME_ENTRY, currentIRFunc);
    const auto condBlock = cg.createBlock();
    const auto bodyBlock = cg.createBlock();
    const auto exitBlock = cg.createBlock();
    const auto trueBlock = cg.createBlock();
    const auto falseBlock = cg.createBlock();
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush(func->hasDefers, func->needsCleanup());

    const auto dArray = originalArr.type->asDArray();
    LgsArrayExpr newArr(dArray);
    visitArrayExpr(&newArr);

    const auto iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    const auto loopStart = cg.builder.CreateSExt(cg.sizeZero(), cg.sizeTy());
    cg.builder.CreateStore(loopStart, iPtr);
    cg.builder.CreateBr(condBlock);

    // Condition
    cg.startBlock(condBlock);
    const auto iValue = cg.builder.CreateLoad(cg.sizeTy(), iPtr);
    const auto condition = cg.builder.CreateICmpSLT(iValue, dArray->lengthIR(cg, func->funcType->params[0].IRValue));
    cg.builder.CreateCondBr(condition, bodyBlock, exitBlock);

    // Body
    cg.startBlock(bodyBlock);
    const auto element = dArray->getIRElement(cg, originalArr.IRValue, iValue);
    const auto ft = dyn_cast<FunctionType>(callback.type->getIRType(cg));
    const auto arg = cg.builder.CreateLoad(dArray->baseType->getIRType(cg), element);
    const auto v = cg.builder.CreateCall(ft, callback.IRValue, {arg});

    cg.builder.CreateCondBr(v, trueBlock, falseBlock);
    cg.startBlock(trueBlock);
    dArray->getAddFunc()->callIR(cg, {newArr.IRValue, element});
    cg.builder.CreateBr(falseBlock);
    cg.startBlock(falseBlock);

    // Increment
    const auto inc = cg.builder.CreateAdd(iValue, cg.usize(1));
    cg.builder.CreateStore(inc, iPtr);
    cg.builder.CreateBr(condBlock);

    // End func
    cg.startBlock(exitBlock);
    cg.callPopStack(func->hasDefers, func->needsCleanup());
    cg.builder.CreateRet(newArr.IRValue);

    // Restore state
    currentIRFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    func->IRValue = func->getIRFunc(cg);
}

Value* LgsCodeGen::getIRValue(LgsValue* value) {
    if (value->IRValue) return value->IRValue;
    if (const auto expr = dynamic_cast<LgsExpr*>(value)) {
        visitExpr(expr);
    } else if (const auto stmt = dynamic_cast<LgsStmt*>(value)) {
        visitStmt(stmt);
    } else if (const auto param = dynamic_cast<LgsParam*>(value)) {
        visitParam(param);
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
