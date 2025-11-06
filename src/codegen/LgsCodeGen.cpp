#include "codegen/LgsCodeGen.h"
#include "builtins/LgsTest.h"
#include "data/LgsConfigs.h"
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
#include "logos/LgsApp.h"
#include "logos/LgsAppConfigs.h"
#include "logos/LgsPaths.h"
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
#include <llvm/IR/Module.h>
#include "llvm/IR/Verifier.h"
#include <llvm/Support/FileSystem.h>
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <iostream>
#include <unistd.h>
#include <unordered_set>

std::atomic<size_t> LgsCodeGen::namesCounter{0};
#define GENERATE_OBJ_CMD_STRING "llc -filetype=obj -o %s %s.bc"

bool LgsCodeGen::generate() {
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
    if (appConfigs.debugMode) cg.finalizeDebugger(paths.buildDir);
    return writeIRModule();
}

void LgsCodeGen::visitMainFile(LgsMainFile* mainFile) {
    for (const auto interface : mainFile->interfaces) {
        visitInterface(interface);
    }
    for (const auto object : mainFile->objects) {
        visitObject(object);
    }
    for (const auto& [_, func] : mainFile->funcs) {
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
    cg.callLgsFunc("Runtime_close", cg.voidTy());
    cg.builder.CreateRet(cg.i32(EXIT_SUCCESS));
    stack.exitScope();
}

void LgsCodeGen::visitFunc(LgsFunc* func) {
    if (func->funcType->isGeneric) return;
    stack.enterScope(func);
    createPrologue(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    if (func->funcType->rt->isVoid() && !cg.lastInstTerminator()) {
        cg.builder.CreateRetVoid();
    }
    stack.exitScope();
}

void LgsCodeGen::visitGenericFunc(LgsFunc* func) {
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = currentIRFunc;
    stack.enterScope(func);
    createPrologue(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func);
    if (func->funcType->rt->isVoid() && !cg.lastInstTerminator()) {
        cg.builder.CreateRetVoid();
    }
    stack.exitScope();
    currentIRFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
}

void LgsCodeGen::visitField(LgsField* field) const {
    if (const auto vec = field->type->asVec()) {
        std::vector<int> mask(vec->vectorDim);
        for (int8_t i = 0; i < vec->vectorDim; i++) {
            mask[i] = LgsVec::getComponentIndex(field->name[i]);
        }
        const llvm::ArrayRef maskRef(mask);
        const auto vecType = field->type->getIRType(cg);
        field->IRValue = cg.builder.CreateAlloca(vecType);
        const auto l = cg.builder.CreateLoad(field->parent->getIRType(cg), field->parentIRValue);
        const auto newVec = cg.builder.CreateShuffleVector(l, UndefValue::get(field->parent->getIRType(cg)), maskRef);
        cg.builder.CreateStore(newVec, field->IRValue);
    } else {
        field->IRValue = field->getGEP(cg);
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
        const auto vaStart = llvm::Intrinsic::getDeclaration(cg.IRModule, llvm::Intrinsic::vastart, {cg.builder.getPtrTy()});
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
    if (stack.currentFunc()->funcType->isCoroutine) {
        yield();
    }
    loop->incAndJumpToCond(cg);
    cg.startBlock(loop->IRExitBlock);
    stack.exitScope();
}

void LgsCodeGen::visitRangeLoop(LgsRangeLoop* loop) {
    visitExpr(loop->startRange);
    visitExpr(loop->endRange);
    const auto indexType = loop->endRange->IRValue->getType();
    loop->iPtr = cg.builder.CreateAlloca(indexType);

    const auto loopStart = loop->loopStart(cg);
    const auto loopEnd = loop->loopEnd(cg);

    // Determine direction
    const auto isReversed = cg.builder.CreateICmpSLT(loopStart, loopEnd);
    cg.builder.CreateStore(loopStart, loop->iPtr);
    cg.builder.CreateBr(loop->IRCondBlock);

    // Condition
    cg.startBlock(loop->IRCondBlock);
    loop->iValue = cg.builder.CreateLoad(cg.i32Ty(), loop->iPtr);
    const auto condForward = cg.builder.CreateICmpSLT(loop->iValue, loopEnd);
    const auto condReverse = cg.builder.CreateICmpSGT(loop->iValue, loopEnd);
    const auto condition = cg.builder.CreateSelect(isReversed, condForward, condReverse);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock);
    if (!loop->loopVars.empty()) {
        loop->loopVars[0]->IRValue = loop->iValue;
    }
    loop->isReversed = isReversed;
}

void LgsCodeGen::visitForeachLoop(LgsForeachLoop* loop) {
    visitExpr(loop->iterExpr);
    const auto indexTy = cg.i64Ty();
    loop->iPtr = cg.builder.CreateAlloca(indexTy);
    cg.builder.CreateStore(cg.i64Zero(), loop->iPtr);
    const auto loopEnd = cg.builder.CreateSExt(loop->loopEnd(cg), indexTy);
    cg.branchAndStartBlock(loop->IRCondBlock);

    loop->iValue = cg.builder.CreateLoad(cg.i32Ty(), loop->iPtr);
    const auto condition = cg.builder.CreateICmpSLT(loop->iValue, loopEnd);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);
    cg.startBlock(loop->IRBodyBlock);

    const auto iterable = loop->iterExpr->type->asIterable();
    iterable->unpackLoopIR(cg, loop);
}

void LgsCodeGen::visitInfiniteLoop(const LgsInfiniteLoop* loop) const {
    cg.branchAndStartBlock(loop->IRBodyBlock);
}

void LgsCodeGen::visitLoopMetaVar(LgsLoopMetaVar* metaVar) {
    const auto loop = stack.currentLoop();
    const auto iValue = loop->iValue;
    switch (metaVar->varType) {
    case FOR_I: {
        metaVar->IRValue = iValue;
        break;
    }
    case FOR_IS_FIRST: {
        const auto loopStart = cg.builder.CreateSExt(loop->loopStart(cg), cg.i64Ty());
        metaVar->IRValue = cg.builder.CreateICmpEQ(iValue, loopStart);
        break;
    }
    case FOR_IS_LAST: {
        const auto loopEnd = cg.builder.CreateSExt(loop->loopEnd(cg), cg.i64Ty());
        const auto decremented = cg.builder.CreateSub(loopEnd, cg.i64(1));
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
        visitExpr(varDec->expr);
        if (varDec->expr->IRValue != varDec->IRValue) {
            cg.builder.CreateStore(varDec->expr->IRValue, varDec->IRValue);
        }
    } else {
        visitExpr(varDec->expr);
        varDec->IRValue = varDec->expr->IRValue;
    }
    assert(varDec->IRValue);
    varDec->IRValue->setName(varDec->name);
    if (appConfigs.debugMode) varDec->setDebugValue(cg);
}

void LgsCodeGen::visitAssignment(const LgsAssignment* assignment) {
    const auto lValue = assignment->lValue;
    const auto rValue = assignment->rValue;
    if (const auto iterIndex = lValue->asIterIndex()) {
        visitIterIndex(iterIndex, true);
    } else if (const auto var = lValue->asVariable()) {
        visitVariable(var);
    } else if (const auto selection = lValue->asSelection()) {
        visitSelection(selection, true);
    } else {
        assert(0);
    }
    assignment->rValue->destPtrValue = lValue->IRValue;
    visitExpr(assignment->rValue, true);

    Value* results = nullptr;
    switch (assignment->assignmentType) {
    case ASSIGN: lValue->assign(cg, rValue); return;
    case ASSIGN_ADD: results = lValue->type->addIR(cg, lValue, rValue); break;
    case ASSIGN_SUB: results = lValue->type->subIR(cg, lValue, rValue); break;
    case ASSIGN_MUL: results = lValue->type->mulIR(cg, lValue, rValue); break;
    case ASSIGN_DIV: results = lValue->type->divIR(cg, lValue, rValue); break;
    case ASSIGN_MOD: results = lValue->type->modIR(cg, lValue, rValue); break;
    case ASSIGN_AND: results = lValue->type->bitAndIR(cg, lValue, rValue); break;
    case ASSIGN_OR: results = lValue->type->bitOrIR(cg, lValue, rValue); break;
    case ASSIGN_XOR: results = lValue->type->bitXorIR(cg, lValue, rValue); break;
    case ASSIGN_LSHIFT: results = lValue->type->lshiftIR(cg, lValue, rValue); break;
    case ASSIGN_RSHIFT: results = lValue->type->rshiftIR(cg, lValue, rValue); break;
    case ASSIGN_UNKNOWN: break;
    }
    assert(results);
    cg.builder.CreateStore(results, lValue->IRValue);
}

void LgsCodeGen::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->elseIfs.empty()) {
        if (ifStmt->elseBlock) {
            visitIfWithElse(ifStmt);
        } else {
            visitSimpleIf(ifStmt);
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

    for (size_t i = 0; i < ifStmt->elseIfs.size(); ++i) {
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
    const auto defaultBlock = cg.createBlock("", currentIRFunc);
    const auto exitBlock = cg.createBlock("", currentIRFunc);
    visitExpr(pm->cond);

    const auto exprIRValue = pm->cond->hash(cg);
    llvm::SwitchInst* switchInst;
    if (pm->elseBlock) {
        const auto numOfCases = pm->patterns.size();
        switchInst = cg.builder.CreateSwitch(exprIRValue, defaultBlock, numOfCases);
    } else {
        switchInst = cg.builder.CreateSwitch(exprIRValue, exitBlock, pm->patterns.size());
    }

    for (size_t i = 0; i < pm->patterns.size(); ++i) {
        stack.enterScope(pm);
        const auto [expr, stmtsBlock] = pm->patterns[i];
        visitExpr(expr);
        const auto patternBlock = cg.createBlock(BLOCK_NAME_CASE_PREFIX + std::to_string(i), currentIRFunc);
        const auto hashed = expr->hash(cg);
        switchInst->addCase(llvm::dyn_cast<ConstantInt>(hashed), patternBlock);
        cg.builder.SetInsertPoint(patternBlock);
        visitStmtsBlock(stmtsBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    if (pm->elseBlock) {
        stack.enterScope(pm);
        cg.builder.SetInsertPoint(defaultBlock);
        visitStmtsBlock(pm->elseBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }
    cg.builder.SetInsertPoint(exitBlock);
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

    const auto funcName = fc->func->getIRName();
    if (!cg.IRModule->getFunction(funcName)) {
        cg.savedIP = cg.builder.saveIP();
        const auto originalFunc = currentIRFunc;
        visitFunc(fc->func);
        currentIRFunc = originalFunc;
        cg.builder.restoreIP(cg.savedIP);
    }

    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.callLgsFunc("Scheduler_addCoro", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {func, ctx});
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
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.callLgsFunc("Stack_addDefer", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {func, ctx});
}

void LgsCodeGen::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitExpr(ioStmt->varDec->expr);
    visitStmtsBlock(ioStmt->stmtsBlock);
}

void LgsCodeGen::visitExpr(LgsExpr* expr, const bool assign) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        if (iter->size && !iter->size->IRValue) {
            visitExpr(iter->size);
        }
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
    if (binExpr->isValueKnown) {
        assert(binExpr->results);
        visitExpr(binExpr->results);
        binExpr->IRValue = binExpr->results->IRValue;
        return;
    }
    switch (binExpr->op) {
    case ADD: binExpr->IRValue = binExpr->type->addIR(cg, l, r); break;
    case SUB: binExpr->IRValue = binExpr->type->subIR(cg, l, r); break;
    case MUL: binExpr->IRValue = binExpr->type->mulIR(cg, l, r); break;
    case DIV: binExpr->IRValue = binExpr->type->divIR(cg, l, r); break;
    case MODULO: binExpr->IRValue = binExpr->type->modIR(cg, l, r); break;
    case BIT_AND: binExpr->IRValue = binExpr->type->bitAndIR(cg, l, r); break;
    case BIT_OR: binExpr->IRValue = binExpr->type->bitOrIR(cg, l, r); break;
    case BIT_XOR: binExpr->IRValue = binExpr->type->bitXorIR(cg, l, r); break;
    case LSHIFT: binExpr->IRValue = binExpr->type->rshiftIR(cg, l, r); break;
    case RSHIFT: binExpr->IRValue = binExpr->type->lshiftIR(cg, l, r); break;
    case EQ: binExpr->IRValue = binExpr->type->eqIR(cg, l, r); break;
    case NE: binExpr->IRValue = binExpr->type->neIR(cg, l, r); break;
    case LT: binExpr->IRValue = binExpr->type->ltIR(cg, l, r); break;
    case GT: binExpr->IRValue = binExpr->type->gtIR(cg, l, r); break;
    case GE: binExpr->IRValue = binExpr->type->geIR(cg, l, r); break;
    case LE: binExpr->IRValue = binExpr->type->leIR(cg, l, r); break;
    case AND: binExpr->IRValue = binExpr->type->andIR(cg, l, r); break;
    case OR: binExpr->IRValue = binExpr->type->orIR(cg, l, r); break;
    case IN: binExpr->IRValue = r->type->asIterable()->inIR(cg, r, l); break;
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
        if (variable->ref.param->isSelf) {
            variable->IRValue = currentIRFunc->getArg(0);
        } else {
            variable->IRValue = variable->ref.param->IRValue;
        }
        break;
    case FUNC:
        variable->IRValue = variable->ref.func->getIRFunc(cg);
        break;
    case OBJECT:
        variable->IRValue = getIRValue(variable->ref.object->singleton);
        break;
    case FIELD:
        if (variable->ref.field->type->asEnum()) {
            variable->IRValue = cg.usize(variable->ref.field->position);
        } else {
            variable->IRValue = variable->ref.field->getGEP(cg);
        }
        break;
    case GENERIC:
    case ENUM:
    case INTERFACE:
    case SUBTYPE:
        return;
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCodeGen::visitSelection(LgsSelection* selection, const bool assign) {
    const auto firstExpr = selection->exprs.front();
    if (!firstExpr->isImportName) {
        visitExpr(firstExpr);
        assert(!firstExpr->IRValue || &firstExpr->IRValue->getContext() == &cg.IRModule->getContext());
    }
    for (size_t i = firstExpr->isImportName; i < selection->exprs.size() - 1; ++i) {
        const auto parent = selection->exprs[i];
        const auto child = selection->exprs[i + 1];
        if (const auto var = child->asVariable()) {
            visitFieldSelection(var, parent, assign);
        } else if (const auto methodCall = child->asFuncCall()) {
            const bool isTest = stack.currentFunc()->isTest && parent->type->getName() == LgsTest::name && methodCall->name == "mock";
            if (isTest) continue;
            visitFuncCall(methodCall);
        } else if (const auto iterIndex = child->asIterIndex()) {
            const auto baseExpr = iterIndex->getBaseExpr()->asVariable();
            const auto field = parent->type->getField(baseExpr->name);
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

void LgsCodeGen::visitFieldSelection(LgsVariable* var, LgsExpr* parent, const bool assign) const {
    if (var->ref.symbolType == FUNC) {
        var->IRValue = var->ref.func->getIRFunc(cg);
        return;
    }

    const auto field = var->ref.field;
    if (field->isEnumField) {
        var->IRValue = cg.usize(field->position);
        return;
    }

    if (field->type->asEnum()) {
        if (assign) {
            field->parentIRValue = parent->IRValue;
            var->IRValue = field->getGEP(cg);
        } else {
            var->IRValue = cg.builder.CreateLoad(cg.sizeTy(), field->getGEP(cg));
        }
        return;
    }

    if (parent->asTypeExpr()) {
        const auto object = parent->type->asObject();
        if (object && object->singleton) {
            if (cg.IRModule->getName().str() == LGS_MAIN_FILE) {
                field->parentIRValue = object->singleton->IRValue;
            } else {
                field->parentIRValue = cg.IRModule->getOrInsertGlobal(object->name, object->getIRType(cg));
            }
            field->IRValue = field->getGEP(cg);
        }
    } else {
        field->parentIRValue = parent->IRValue;
        field->IRValue = field->getGEP(cg);
        assert(parent->IRValue && &parent->IRValue->getContext() == &cg.IRModule->getContext());
    }

    if (field->type->asObject() || (field->type->asEnum() && !assign)) {
        var->IRValue = cg.builder.CreateLoad(cg.ptrTy(), field->IRValue);
    } else {
        var->IRValue = field->IRValue;
    }
}

void LgsCodeGen::visitFuncCall(LgsFuncCall* funcCall) {
    for (size_t i = funcCall->isMethodCall; i < funcCall->args.size(); ++i) {
        visitExpr(funcCall->args[i]);
    }

    if (funcCall->ref.symbolType == PARAM) {
        LgsFunc func(nullptr);
        func.funcType = funcCall->ref.param->type->asFuncType();
        func.setType(func.funcType);
        func.IRValue = getIRValue(funcCall->ref.param);
        funcCall->func = &func;
    } else if (funcCall->ref.symbolType == VAR_DEC) {
        LgsFunc func(nullptr);
        func.funcType = funcCall->ref.varDec->type->asFuncType();
        func.setType(func.funcType);
        func.IRValue = getIRValue(funcCall->ref.varDec);
        funcCall->func = &func;
    }

    const auto ft = funcCall->func->funcType;
    if (ft->hasDefaults) {
        const auto diff = ft->params.size() - funcCall->args.size() - 1;
        for (size_t i = diff; i < ft->params.size(); ++i) {
            visitExpr(ft->params[i].expr);
        }
    }

    if (ft->isVirtual) {
        const auto self = funcCall->selfPtr;
        const auto keyIR = cg.getIRStr(ft->name);
        funcCall->func->IRValue = cg.callGetFromVTable(self->IRValue, keyIR);
    } else if (funcCall->func->funcType->isArrFunc) {
        visitIterFunc(funcCall);
    }
    if (funcCall->isCoroutine || funcCall->isDeferred) return;

    if (funcCall->func->funcType->isGeneric) visitGenericFunc(funcCall->func);
    funcCall->IRValue = funcCall->func->call(cg, funcCall->args, funcCall->generics);

    if (appConfigs.debugMode) funcCall->setDebugValue(cg);
}

void LgsCodeGen::visitIterFunc(const LgsFuncCall* funcCall) {
    if (funcCall->name == MAP_FUNC_NAME) {
        return createMapFunc(funcCall->func);
    }
    if (funcCall->name == FILTER_FUNC_NAME) {
        return createFilterFunc(funcCall->func);
    }
    if (funcCall->name == FOREACH_FUNC_NAME) {
        assert(0);
    }
    assert(0);
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
        visitField(field);
        visitExpr(field->expr);
        cg.builder.CreateStore(exprIR, field->IRValue);
    }

    // Zero values
    for (const auto field : instance->obj->fields) {
        if (visited.contains(field->name) || field->type->asEnum()) continue;
        field->parentIRValue = instance->IRValue;
        if (!field->expr) {
            field->expr = field->type->getZeroValue();
            if (field->isOwner && field->type->isHeapAlloc) {
                field->expr->owner = field;
            }
        }
        field->IRValue = field->getGEP(cg);
        if (field->expr) {
            field->expr->destPtrValue = field->IRValue;
        }
        visitExpr(field->expr);
        if (field->expr->IRValue == field->IRValue) continue;
        cg.builder.CreateStore(field->expr->IRValue, field->IRValue);
    }
    if (obj->implements.empty()) return;
    resolveVirtuals(instance);
}

void LgsCodeGen::visitIterIndex(LgsIterIndex* iterIndex, const bool assign) {
    visitExpr(iterIndex->baseExpr);
    visitExpr(iterIndex->index.from);
    if(iterIndex->index.to) {
        visitExpr(iterIndex->index.to);
        iterIndex->setRangeIRElementPtr(cg, assign);
    } else {
        iterIndex->setIRElementPtr(cg, assign);
    }
}

void LgsCodeGen::visitNull(LgsNull* null) const {
    null->IRValue = cg.null();
}

void LgsCodeGen::visitJson(LgsJson* json) {
    assert(0);
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

void LgsCodeGen::createPrologue(LgsFunc* func) {
    if (func->isTest) for (auto [_, then] : func->mocks) visitExpr(then);
    if (appConfigs.debugMode) func->setDebugValue(cg);
    currentIRFunc = func->getIRFunc(cg);
    const auto entryBlock = cg.createBlock(BLOCK_NAME_ENTRY, currentIRFunc);
    cg.builder.SetInsertPoint(entryBlock);
    if (func->funcType->name == LGS_MAIN_FUNC) {
        cg.callLgsFunc("Runtime_init", cg.voidTy());
    }
    cg.callStackPush(func->hasDefers, func->needsCleanup());
    // if (func->funcType->isVariadic) {
    //     const auto& variadicParam = func->funcType->params.back();
    //     const auto valist = cg.builder.CreateAlloca(cg.ptrTy());
    //     const auto ty = variadicParam.type->getIRType(cg);
    //     cg.callIntrinsics(llvm::Intrinsic::vastart, {valist}, {cg.ptrTy()});
    //     cg.loop(func->variadicCount, [this, ty, valist](Value*, BasicBlock*) {
    //         const auto v = cg.builder.CreateVAArg(valist, ty);
    //         cg.printInt(v);
    //     });
    //     cg.callIntrinsics(llvm::Intrinsic::vaend, {valist}, {cg.ptrTy()});
    // }
}

void LgsCodeGen::createEpilogue(LgsFunc* func) {
    const auto needsCleanup = func->needsCleanup();
    if (!func->hasDefers && !needsCleanup) {
        cg.callPopStack(false, false);
        return;
    }
    cg.branchAndStartBlock(func->getCleanupBlock(cg));
    if (func->hasDefers) cg.callLgsFunc("Stack_callDefers", cg.voidTy());
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
            llvm::PHINode *phi = nullptr;
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

void LgsCodeGen::initMainArgs(const LgsMainFunc* mainFunc) const {
    const auto ft = mainFunc->funcType;
    if (ft->params.empty()) return;
    const auto argsArray = ft->params.front().expr->asArrayExpr();
    const auto sArray = argsArray->type->asSArray();
    sArray->size->IRValue = currentIRFunc->getArg(0);
    argsArray->IRValue = currentIRFunc->getArg(1);
    mainFunc->funcType->params[0].IRValue = argsArray->IRValue;
}

Value* LgsCodeGen::getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) const {
    if (fc->args.empty()) return cg.null();
    const auto ctx = cg.builder.CreateAlloca(ctxTy);
    for (size_t i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i]->IRValue;
        const auto fieldPtr = cg.builder.CreateStructGEP(llvm::dyn_cast<StructType>(ctxTy), ctx, i);
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
    for (size_t i = 0; i < fc->args.size(); i++) {
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

void LgsCodeGen::yield() const {
    const auto doYieldBlock = cg.createBlock("do_yield_block", currentIRFunc);
    const auto continueBlock = cg.createBlock("continue_block", currentIRFunc);
    const auto shouldYield = cg.callLgsFunc("Scheduler_shouldYield", cg.i1Ty());
    cg.builder.CreateCondBr(shouldYield, doYieldBlock, continueBlock);
    cg.builder.SetInsertPoint(doYieldBlock);
    cg.callLgsFunc("Scheduler_yield", cg.voidTy());
    cg.branchIfNeeded(continueBlock);
    cg.builder.SetInsertPoint(continueBlock);
}

void LgsCodeGen::setStaticArray(LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asSArray();
    const auto arrTypeIR = arr->getIRType(cg);
    if (!arrayExpr->destPtrValue && !arrayExpr->IRValue) {
        arrayExpr->IRValue = cg.builder.CreateAlloca(arrTypeIR);
    }
    if (arrayExpr->elements.empty()) return;
    if (arr->baseType->asIterable()) {
        setNestedSArr(arrayExpr, arrTypeIR, arrayExpr->IRValue, {cg.i32Zero()});
    } else {
        for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
            const auto element = arrayExpr->elements[i];
            element->destPtrValue = arrayExpr->IRValue;
            visitExpr(element);
            const auto gep = cg.builder.CreateInBoundsGEP(arrTypeIR, arrayExpr->IRValue, {cg.i32Zero(), cg.i32(i)});
            cg.builder.CreateStore(element->IRValue, gep);
        }
    }
}

void LgsCodeGen::setNestedSArr(const LgsArrayExpr* arrayExpr, Type* parentType, Value* parentValue, const std::vector<Value*>& indices) {
    for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
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
    if (!arrayExpr->IRValue) {
        arrayExpr->IRValue = cg.callMalloc(arr->getSizeBytes(), arrayExpr->owner, arr->getRTType());
    }
    arr->initArr(cg, arrayExpr->IRValue);
    const auto rtt = arr->baseType->getRTType();
    cg.addHeap(arrayExpr->owner, rtt, arrayExpr->IRValue);
    for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
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

    for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
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
    const auto ft = llvm::dyn_cast<FunctionType>(callback.type->getIRType(cg));
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
    const auto ft = llvm::dyn_cast<FunctionType>(callback.type->getIRType(cg));
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

bool LgsCodeGen::writeIRModule() const {
    if (verifyModule(*cg.IRModule, &llvm::errs())) return false;
    // Write IR to file
    auto moduleName = cg.IRModule->getName().str();
    if (lgsConfigs.writeIRFiles) {
        const auto filePath = (paths.buildDirIR / moduleName).string() + ".ll";
        if (fs::exists(filePath)) fs::remove(filePath);
        std::error_code EC;
        raw_fd_ostream textFile(filePath, EC, llvm::sys::fs::OF_None);
        cg.IRModule->print(textFile, nullptr);
    }

    // Run pass
    llvm::PassBuilder builder(targetMachine);
    llvm::LoopAnalysisManager loopAnalyser;
    llvm::FunctionAnalysisManager funcAnalyser;
    llvm::CGSCCAnalysisManager CGAnalyser;
    llvm::ModuleAnalysisManager analysisManager;
    builder.registerModuleAnalyses(analysisManager);
    builder.registerFunctionAnalyses(funcAnalyser);
    builder.registerLoopAnalyses(loopAnalyser);
    builder.registerCGSCCAnalyses(CGAnalyser);
    builder.crossRegisterProxies(loopAnalyser, funcAnalyser, CGAnalyser, analysisManager);

    const auto optLevel = cg.getOptLevel(appConfigs.optLevel);
    auto passManager = builder.buildPerModuleDefaultPipeline(optLevel);
    passManager.run(*cg.IRModule, analysisManager);

    // Create bc file
    std::error_code ec;
    const std::string outputPath = paths.buildDirObjs / (moduleName + ".o");
    if (fs::exists(outputPath)) fs::remove(outputPath);
    raw_fd_ostream bitcodeStream(outputPath + ".bc", ec, llvm::sys::fs::OF_None);
    assert(!ec);
    llvm::WriteBitcodeToFile(*cg.IRModule, bitcodeStream);
    bitcodeStream.flush();
    bitcodeStream.close();

    // Create object
    char cmd[1024*4];
    std::snprintf(cmd, sizeof(cmd), GENERATE_OBJ_CMD_STRING, outputPath.c_str(), outputPath.c_str());
    if (std::system(cmd) != 0) assert(0);
    fs::remove(outputPath + ".bc");
    return true;
}
