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
#include "types/LgsInterface.h"
#include "loops/LgsForLoop.h"
#include "loops/LgsForeachLoop.h"
#include "loops/LgsInfiniteLoop.h"
#include "loops/LgsRangeLoop.h"
#include "loops/LgsWhileLoop.h"
#include "stmts/LgsAssignment.h"
#include "stmts/LgsIOStmt.h"
#include "stmts/LgsIfStmt.h"
#include "types/iterables/LgsSArray.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsSize.h"
#include <llvm/IR/Module.h>
#include <llvm/Target/TargetMachine.h>

std::atomic<size_t> LgsCodeGen::namesCounter{0};

void LgsCodeGen::generate(const LgsAppConfigs& appConfigs, TargetMachine& targetMachine) {
    cg.targetMachine = &targetMachine;
    cg.setupModule(file, appConfigs.debugMode);
    if (const auto mainFile = dynamic_cast<LgsMainFile*>(&file)) {
        visitMainFile(mainFile);
    } else if (const auto objFile = dynamic_cast<LgsObjectFile*>(&file)) {
        visitObjFile(objFile);
    } else if (const auto interfaceFile = dynamic_cast<LgsInterfaceFile*>(&file)) {
        visitInterfaceFile(interfaceFile);
    } else if (const auto testFile = dynamic_cast<LgsTestFile*>(&file)) {
        visitTestFile(testFile);
    }
}

void LgsCodeGen::visitMainFile(LgsMainFile* mainFile) {
    for (const auto object : mainFile->objects) {
        const auto objIRType = object->getIRType(cg);
        if(const auto singleton = object->singleton) {
            const auto zeroInit = ConstantAggregateZero::get(objIRType);
            singleton->IRValue = cg.createGlobal(objIRType, zeroInit, object->name);
        }
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
    const auto obj = objFile->obj;
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

void LgsCodeGen::visitInterfaceFile(const LgsInterfaceFile* interfaceFile) {
    for (const auto& [_, method] : interfaceFile->interface->methods) {
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

void LgsCodeGen::visitMainFunc(LgsMainFunc* func) {
    stack.enterScope(func);
    createPrologue(func);
    cg.callLgsFunc("runtime_init", cg.voidTy());
    if (!func->funcType->params.empty()) initMainArgs(func);
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
    if (!cg.lastInstTerminator()) cg.builder.CreateRetVoid();
    stack.exitScope();
}

void LgsCodeGen::visitGroup(LgsGroup* group) {
    assert(0);
}

void LgsCodeGen::visitField(LgsField* field) {
    visitExpr(field->expr);
    if (const auto vec = field->type->asVec()) {
        std::vector<int> mask(vec->dim);
        for (unsigned i = 0; i < vec->dim; i++) {
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
    if (const auto pattern = stmt->asPattern()) return visitPatternMatching(pattern);
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
    iterable->unpackLoopVarsIR(cg, loop->loopVars, loop->iterExpr->IRValue, loop->iValue);
}

void LgsCodeGen::visitInfiniteLoop(const LgsInfiniteLoop* loop) const {
    cg.branchAndStartBlock(loop->IRBodyBlock);
}

void LgsCodeGen::visitLoopMetaVar(LgsLoopMetaVar* metaVar) {
    const auto loop = metaVar->forLoop;
    const auto iValue = loop->iValue;
    switch (metaVar->varType) {
    case FOR_I: {
        metaVar->IRValue = iValue;
        break;
    }
    case FOR_PREV: {
        const auto i = cg.builder.CreateSub(loop->loadIndex(cg), cg.usize(1));
        if (loop->asRangeLoop()) {
            metaVar->IRValue = i;
        } else if (const auto foreachLoop = loop->asForeachLoop()) {
            const auto indexFrom = new LgsIntConst(&LGS_SIZE, 0);
            auto iterIndex = LgsIterIndex(foreachLoop->iterExpr, indexFrom);
            visitIterIndex(&iterIndex);
            indexFrom->IRValue = i;
            metaVar->IRValue = iterIndex.loadIR(cg);
            assert(0);
        }
        break;
    }
    case FOR_NEXT: {
        const auto i = cg.builder.CreateAdd(loop->loadIndex(cg), cg.usize(1));
        if (loop->asRangeLoop()) {
            metaVar->IRValue = i;
        } else if (const auto foreachLoop = loop->asForeachLoop()) {
            const auto indexFrom = new LgsIntConst(&LGS_SIZE, 0);
            auto iterIndex = LgsIterIndex(foreachLoop->iterExpr, indexFrom);
            visitIterIndex(&iterIndex);
            indexFrom->IRValue = i;
            metaVar->IRValue = iterIndex.loadIR(cg);
            assert(0);
        }
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
    visitExpr(varDec->expr);
    if (shouldAllocate(varDec)) {
        const auto IRType = varDec->type->getIRType(cg);
        varDec->IRValue = cg.builder.CreateAlloca(IRType, nullptr, varDec->name);
        cg.builder.CreateStore(varDec->expr->IRValue, varDec->IRValue);
    } else {
        varDec->expr->IRValue->setName(varDec->name);
        varDec->IRValue = varDec->expr->IRValue;
    }
}

void LgsCodeGen::visitAssignment(const LgsAssignment* assignment) {
    visitExpr(assignment->lValue);
    visitExpr(assignment->rValue);
    Value* results = nullptr;
    switch (assignment->assignmentType) {
    case ASSIGN: assignment->lValue->assign(cg, assignment->rValue); return;
    case ASSIGN_ADD: results = assignment->lValue->type->addIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_SUB: results = assignment->lValue->type->subIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_MUL: results = assignment->lValue->type->mulIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_DIV: results = assignment->lValue->type->divIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_MOD: results = assignment->lValue->type->modIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_AND: results = assignment->lValue->type->bitAndIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_OR: results = assignment->lValue->type->bitOrIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_XOR: results = assignment->lValue->type->bitXorIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_LSHIFT: results = assignment->lValue->type->lshiftIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    case ASSIGN_RSHIFT: results = assignment->lValue->type->rshiftIR(cg, assignment->lValue->IRValue, assignment->rValue->IRValue); break;
    }
    assert(results);
    cg.builder.CreateStore(results, assignment->lValue->IRValue);
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

void LgsCodeGen::visitPatternMatching(LgsPatternMatching* pm) {
    const auto defaultBlock = cg.createBlock(BLOCK_NAME_DEFAULT_CASE);
    const auto exitBlock = cg.createBlock(BLOCK_NAME_EXIT_PATTERN);

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
        const auto [expr, stmtsBlock] = pm->patterns[i];
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
        cg.startBlock(defaultBlock);
        cg.builder.CreateBr(exitBlock);
        stack.exitScope();
    }

    cg.startBlock(exitBlock);
}

void LgsCodeGen::visitCoroutine(const LgsCoroutine* coroutine) {
    const LgsFuncCall* fc = nullptr;
    if (coroutine->funcCall) {
        visitFuncCall(coroutine->funcCall);
        fc = coroutine->funcCall;
    } else if (coroutine->selection) {
        visitSelection(coroutine->selection);
        fc = coroutine->selection->asMethodCall();
    } else {
        assert(0);
    }
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.callLgsFunc("stack_addCoro", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {func, ctx});
}

void LgsCodeGen::visitIOStmt(const LgsIOStmt* ioStmt) {
    visitVarDec(ioStmt->varDec);
    visitStmtsBlock(ioStmt->stmtsBlock);
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
        cg.callPopStack(currentFunc->funcType->name);
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
        fc = deferStmt->selection->asMethodCall();
    } else {
        assert(0);
    }
    for (const auto& arg : fc->args) {
        visitExpr(arg);
    }
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto func = getThunkFunc(fc, ctxTy);
    cg.callLgsFunc("stack_addDefer", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {func, ctx});
}

void LgsCodeGen::visitExpr(LgsExpr* expr) {
    if (!expr) return;
    if (const auto iter = expr->type->asIterable()) {
        visitExpr(iter->size);
    }
    if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr);
    } else {
        if (checkMock(expr)) return;
        if (const auto func = expr->asFunc()) return visitLambda(func);
        if (const auto instance = expr->asInstance()) return visitInstance(instance);
        if (const auto funcCall = expr->asFuncCall()) return visitFuncCall(funcCall);
        if (const auto strConst = expr->asStrConst()) return visitStrConst(strConst);
        if (const auto selection = expr->asSelection()) return visitSelection(selection);
        if (const auto arrayExpr = expr->asArrayExpr()) return visitArrayExpr(arrayExpr);
        if (const auto hashMap = expr->asHashMap()) return visitHashMap(hashMap);
        if (const auto iterIndex = expr->asIterIndex()) return visitIterIndex(iterIndex);
        if (const auto variable = expr->asVariable()) return visitVariable(variable);
        if (const auto postfixExpr = expr->asPostfixExpr()) return visitPostfixExpr(postfixExpr);
        if (const auto prefixExpr = expr->asPrefixExpr()) return visitPrefixExpr(prefixExpr);
        if (const auto vecExpr = expr->asVectorExpr()) return visitVectorExpr(vecExpr);
        if (const auto intConst = expr->asIntConst()) return visitIntConst(intConst);
        if (const auto floatConst = expr->asFloatConst()) return visitFloatConst(floatConst);
        if (const auto loopMetaVar = expr->asLoopMetaVar()) return visitLoopMetaVar(loopMetaVar);
        if (const auto cast = expr->asCast()) return visitCast(cast);
        if (const auto typeExpr = expr->asTypeExpr()) return visitTypeExpr(typeExpr);
        if (const auto json = expr->asJson()) return visitJson(json);
        assert(0);
    }
}

void LgsCodeGen::visitBinaryExpr(LgsBinaryExpr* binExpr) {
    visitExpr(binExpr->left);
    visitExpr(binExpr->right);
    switch (binExpr->op) {
    case ADD:
        binExpr->IRValue = binExpr->type->addIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case SUB:
        binExpr->IRValue = binExpr->type->subIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case MUL:
        binExpr->IRValue = binExpr->type->mulIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case DIV:
        binExpr->IRValue = binExpr->type->divIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case IN:
        binExpr->IRValue = binExpr->right->type->asIterable()->inIR(cg, binExpr->right, binExpr->left);
        break;
    case MOD:
        binExpr->IRValue = binExpr->type->modIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case EQ:
        binExpr->IRValue = binExpr->type->eqIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case NE:
        binExpr->IRValue = binExpr->type->neIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case AND:
        binExpr->IRValue = binExpr->type->andIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case OR:
        binExpr->IRValue = binExpr->type->orIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case LT:
        binExpr->IRValue = binExpr->type->ltIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case GT:
        binExpr->IRValue = binExpr->type->gtIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case GE:
        binExpr->IRValue = binExpr->type->geIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case LE:
        binExpr->IRValue = binExpr->type->leIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case BIT_AND:
        binExpr->IRValue = binExpr->type->bitAndIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case BIT_OR:
        binExpr->IRValue = binExpr->type->bitOrIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case BIT_XOR:
        binExpr->IRValue = binExpr->type->bitXorIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case LSHIFT:
        binExpr->IRValue = binExpr->type->rshiftIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case RSHIFT:
        binExpr->IRValue = binExpr->type->lshiftIR(cg, binExpr->left->loadIR(cg), binExpr->right->loadIR(cg));
        break;
    case NOOP: assert(0);
    }
}

void LgsCodeGen::visitCast(LgsCast* lgsCast) {
    visitExpr(lgsCast->toValue);
    lgsCast->IRValue = getIRValue(lgsCast->toValue);
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
    if (array->type->asSArray()) {
        array->IRValue = createStaticArray(array);
    } else if (array->type->asDArray()) {
        array->IRValue = createDynamicArray(array);
    } else if (array->type->asSet()) {
        array->IRValue = createSetExpr(array);
    } else {
        assert(0);
    }
}

void LgsCodeGen::visitHashMap(LgsHashMap* hashMap) {
    const auto map = hashMap->type->asMap();
    const auto valueType = map->typePair->value;
    const auto elementSize = cg.usize(valueType->getSizeBytes());
    const auto arrSize = cg.typeSize(map->getMapStruct(cg));
    hashMap->IRValue = cg.callMalloc(arrSize.getFixedValue(), hashMap->owner, hashMap->type->getRTType());
    LgsFunc initFunc("init", &LGS_VOID, {map, &LGS_LONG}, BUILTIN | METHOD);
    initFunc.callIR(cg, {getIRValue(hashMap), elementSize});
    for (const auto element : hashMap->initialElements) {
        visitExpr(element->key);
        visitExpr(element->value);
        map->getAddFunc()->callIR(cg, {hashMap->IRValue, element->key->IRValue, element->value->IRValue});
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
    case INTERFACE:
    case SUBTYPE:
    case GROUP:
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCodeGen::visitSelection(LgsSelection* selection) {
    visitExpr(selection->exprs.front());
    for (int i = 0; i < selection->exprs.size() - 1; ++i) {
        const auto parent = selection->exprs[i];
        const auto child = selection->exprs[i + 1];
        if (const auto var = child->asVariable()) {
            if (var->ref.symbolType == FUNC) {
                child->IRValue = var->ref.func->getIRFunc(cg);
                continue;
            }
            const auto field = parent->type->getField(var->name);
            if (parent->asTypeExpr()) {
                const auto object = parent->type->asObject();
                if (object && object->singleton) {
                    field->parentIRValue = object->singleton->IRValue;
                    field->parentIRType = object->getIRType(cg);
                    visitField(field);
                    child->IRValue = field->IRValue;
                    continue;
                }
            }
            field->parentIRValue = parent->IRValue;
            field->parentIRType = parent->type->getIRType(cg);
            visitField(field);
            const auto gep = dyn_cast<GetElementPtrInst>(field->IRValue);
            if (gep->getResultElementType()->isPointerTy()) {
                child->IRValue = field->loadIR(cg);
            } else {
                child->IRValue = field->IRValue;
            }
        } else if (const auto methodCall = child->asFuncCall()) {
            const bool isTest = stack.currentFunc()->isTest && parent->type->getName() == LgsTest::name && methodCall->name == "mock";
            if (isTest) continue;
            visitFuncCall(methodCall);
        } else if (const auto iterIndex = child->asIterIndex()) {
            const auto field = parent->type->getField(iterIndex->baseExpr->asVariable()->name);
            field->parentIRValue = parent->IRValue;
            field->parentIRType = parent->type->getIRType(cg);
            visitField(field);
            visitIterIndex(iterIndex);
        } else {
            assert(0);
        }
    }
    selection->IRValue = selection->lastExpr()->IRValue;
}

void LgsCodeGen::visitFuncCall(LgsFuncCall* funcCall) {
    for (int i = 0; i < funcCall->args.size(); ++i) {
        visitExpr(funcCall->args[i]);
    }
    if (funcCall->ref.symbolType == PARAM) {
        LgsFunc f(funcCall->ref.param->type->asFuncType());
        f.IRValue = getIRValue(funcCall->ref.param);
        funcCall->IRValue = f.call(cg, funcCall->args);
        return;
    }
    const auto ft = funcCall->func->funcType;
    if (ft->isVirtual) {
        funcCall->resolveVirtualFunc(cg);
    }
    visitIterFunc(funcCall);
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
    visitExpr(postfixExpr->expr);
    const auto exprAddr = postfixExpr->expr->IRValue;
    const auto exprType = postfixExpr->expr->type->getIRType(cg);
    const auto oldValue = cg.builder.CreateLoad(exprType, exprAddr);
    const auto oneConst = ConstantInt::get(exprType, 1, true);
    switch (postfixExpr->op) {
    case INC: {
        postfixExpr->IRValue = oldValue;
        const auto newValue = cg.builder.CreateAdd(oldValue, oneConst);
        cg.builder.CreateStore(newValue, exprAddr);
        break;
    }
    case DEC: {
        postfixExpr->IRValue = oldValue;
        const auto newValue = cg.builder.CreateSub(oldValue, oneConst);
        cg.builder.CreateStore(newValue, exprAddr);
        break;
    }
    }
}

void LgsCodeGen::visitStrConst(LgsStrConst* strConst) {
    for (const auto templatePart : strConst->templateParts) {
        visitExpr(templatePart);
    }
    strConst->IRValue = cg.getIRStr(strConst->value);
}

void LgsCodeGen::visitIterIndex(LgsIterIndex* iterIndex) {
    visitExpr(iterIndex->baseExpr);
    visitExpr(iterIndex->index.from);
    visitExpr(iterIndex->index.to);
    const auto iter = iterIndex->baseExpr->type->asIterable();
    const auto len = iter->lengthIR(cg, iterIndex->baseExpr->IRValue);
    cg.createBoundsGuard(len, iterIndex->index.from->IRValue);
    iterIndex->setIRElementPtr(cg);
}

void LgsCodeGen::visitInstance(LgsInstance* instance) {
    if (instance->IRValue) return;
    instance->IRValue = cg.callMalloc(instance->obj->getSizeBytes(), instance->owner, instance->obj->getRTType());
    initFields(instance);
    if (!instance->obj->interfaces.empty()) {
        instance->setVirtuals(cg);
    }
}

void LgsCodeGen::visitTypeExpr(LgsTypeExpr* typeExpr) {

}

void LgsCodeGen::visitJson(LgsJson* json) {
    if (const auto instance = json->instance) {
        instance->obj->getIRType(cg);
    } else if (const auto arr = json->arr) {
        visitArrayExpr(arr);
        json->IRValue = arr->IRValue;
    } else if (const auto strConst = json->strConst) {
        visitStrConst(strConst);
        json->IRValue = strConst->IRValue;
    } else if (const auto intConst = json->intConst) {
        visitIntConst(intConst);
        json->IRValue = intConst->IRValue;
    } else if (const auto floatConst = json->floatConst) {
        visitFloatConst(floatConst);
        json->IRValue = floatConst->IRValue;
    } else if (const auto null = json->null) {
        null->IRValue = cg.null();
        json->IRValue = null->IRValue;
    }
}

void LgsCodeGen::initFields(LgsInstance* instance) {
    std::unordered_set<std::string> visited;
    for (const auto& [argName, arg] : instance->args) {
        visited.insert(argName);
        const auto exprIR = getIRValue(arg->expr);
        const auto field = instance->obj->getField(argName);
        field->parentIRValue = instance->IRValue;
        field->parentIRType = instance->obj->getIRType(cg);
        visitField(field);
        cg.builder.CreateStore(exprIR, field->IRValue);
    }

    // Zero values
    for (const auto field : instance->obj->fields) {
        if (visited.count(field->name) || field->type->asEnum()) continue;
        field->parentIRValue = instance->IRValue;
        field->parentIRType = instance->obj->getIRType(cg);
        if (!field->expr) {
            field->expr = field->type->getZeroValue();
            if (field->isOwner && field->type->isHeapAlloc) {
                field->expr->owner = field;
            }
        }
        visitField(field);
        cg.builder.CreateStore(field->expr->IRValue, field->IRValue);
    }
}

bool LgsCodeGen::checkMock(LgsExpr* expr) {
    const auto currentFunc = stack.currentFunc();
    if (currentFunc->isTest) {
        for (auto [when, then] : currentFunc->mocks) {
            if (when->equals(expr)) {
                expr->IRValue = then->IRValue;
                return true;
            }
        }
    }
    return false;
}

bool LgsCodeGen::shouldAllocate(const LgsVarDec* varDec) const {
    const auto type = varDec->type;
    const auto expr = varDec->expr;
    if (type->asVec() || type->asFuncType() || type->isHeapAlloc || (expr->asFuncCall() && type->isNumber())) {
        return false;
    }
    const auto IRType = varDec->type->getIRType(cg);
    return !IRType->isArrayTy() && !IRType->isPointerTy() && !IRType->isVoidTy();
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
    for (auto [_, then] : func->mocks) {
        visitExpr(then);
    }
    currentIRFunc = func->getIRFunc(cg);
    const auto entryBlock = cg.createBlock(BLOCK_NAME_ENTRY, currentIRFunc);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();
}

void LgsCodeGen::createEpilogue(LgsFunc* func) {
    const auto needsCleanup = func->needsCleanup();
    if (!needsCleanup && !func->hasDefers) return;
    cg.branchAndStartBlock(func->getCleanupBlock(cg));
    currentIRFunc = nullptr;
    if (func->hasDefers) cg.callLgsFunc("stack_callDefers", cg.voidTy());

    if (needsCleanup) {
        if (func->returnStmts.empty()) {
            cg.callPopStack(func->funcType->name, true);
        } else if (func->returnStmts.size() == 1) {
            if (func->owners.size() == 1) {
                const auto returnRef = func->returnStmts.front()->expr;
                const auto heapExprRef = func->owners.front();
                if (returnRef->equals(heapExprRef)) {
                    cg.callPopStack(func->funcType->name, true);
                    cg.builder.CreateRet(getIRValue(func->returnStmts.front()));
                    return;
                }
            }
            cg.callPopStack(func->funcType->name, true);
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
            cg.callPopStack(func->funcType->name, true);
            cg.builder.CreateRet(phi);
        }
    } else {
        cg.callPopStack(func->funcType->name);
    }
}

void LgsCodeGen::initMainArgs(LgsMainFunc* mainFunc) {
    auto& builder = cg.builder;
    const std::vector<Type*> structFields{cg.i64Ty(), cg.i32Ty(), cg.i32Ty(), cg.ptrTy()};
    const auto arrStruct = cg.getStructType(structFields, LgsDArray::name);
    mainFunc->mainArgs->IRValue = builder.CreateAlloca(arrStruct);
    mainFunc->initArgsFunc->callIR(cg, {getIRValue(mainFunc->mainArgs), mainFunc->argc, mainFunc->argv});
    mainFunc->funcType->params[0].IRValue = getIRValue(mainFunc->mainArgs);
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

void LgsCodeGen::generateIf(Value* cond, const std::function<void()>& blockStmtCb) const {
    const auto IRBlockIfTrue = cg.createBlock(BLOCK_NAME_IF_TRUE);
    const auto IRBlockIfFalse = cg.createBlock(BLOCK_NAME_IF_FALSE);
    cg.builder.CreateCondBr(cond, IRBlockIfTrue, IRBlockIfFalse);
    cg.startBlock(IRBlockIfTrue);
    blockStmtCb();
    cg.branchAndStartBlock(IRBlockIfFalse);
}

Value* LgsCodeGen::createStaticArray(const LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asSArray();
    const auto baseIRType = arr->baseType->getIRType(cg);
    const auto arraySizeIR = cg.builder.CreateZExt(arr->size->IRValue, cg.sizeTy());
    const auto arrIRPtr = cg.builder.CreateAlloca(baseIRType, arraySizeIR);
    if (arrayExpr->initialElements.empty()) return arrIRPtr;

    const auto elementsNumber = arrayExpr->initialElements.size();
    const auto arrIRType = ArrayType::get(baseIRType, elementsNumber);
    if (allArgsAreConst(arrayExpr->initialElements)) {
        std::vector<Constant*> IRValues;
        for (int i = 0; i < elementsNumber; ++i) {
            const auto element = arrayExpr->initialElements[i];
            IRValues.push_back(dyn_cast<Constant>(getIRValue(element)));
        }
        const auto size = arr->baseType->getSizeBytes() * elementsNumber;
        const auto constArr = cg.createConstGlobal(arrIRType, ConstantArray::get(arrIRType, IRValues));
        cg.callMemCpy(arrIRPtr, constArr, cg.i64(size));
        return arrIRPtr;
    }

    cg.createBoundsGuard(cg.usize(elementsNumber), arraySizeIR);
    for (int i = 0; i < elementsNumber; ++i) {
        const auto element = arrayExpr->initialElements[i];
        const auto gep = cg.builder.CreateGEP(baseIRType, arrIRPtr, cg.i32(i));
        cg.builder.CreateStore(element->IRValue, gep);
    }
    return arrIRPtr;
}

Value* LgsCodeGen::createDynamicArray(LgsArrayExpr* arrayExpr) {
    const auto arr = arrayExpr->type->asDArray();
    const auto size = arr->baseType->getSizeBytes();
    const auto elementSize = cg.i64(size);
    const auto arrSize = cg.typeSize(arr->getArrStruct(cg));
    arrayExpr->IRValue = cg.callMalloc(arrSize.getFixedValue(), arrayExpr->owner, arr->getRTType());
    LgsFunc initFunc("init", &LGS_VOID, {arr, &LGS_LONG}, BUILTIN | METHOD);
    initFunc.callIR(cg, {arrayExpr->IRValue, elementSize});
    for (int i = 0; i < arrayExpr->initialElements.size(); ++i) {
        const auto element = arrayExpr->initialElements[i];
        visitExpr(element);
        arr->getAddFunc()->callIR(cg, {arrayExpr->IRValue, cg.getPtr(element->IRValue)});
    }
    return arrayExpr->IRValue;
}

Value* LgsCodeGen::createSetExpr(LgsArrayExpr* setExpr) {
    const auto arr = setExpr->type->asSet();
    const auto size = arr->baseType->getSizeBytes();
    const auto elementSize = cg.i64(size);
    const auto arrSize = cg.typeSize(arr->getArrStruct(cg));
    setExpr->IRValue = cg.callMalloc(arrSize.getFixedValue(), setExpr->owner, arr->getRTType());
    LgsFunc initFunc("init", &LGS_VOID, {arr, &LGS_LONG}, BUILTIN | METHOD);
    initFunc.callIR(cg, {setExpr->IRValue, elementSize});
    for (int i = 0; i < setExpr->initialElements.size(); ++i) {
        const auto element = setExpr->initialElements[i];
        visitExpr(element);
        arr->getAddFunc()->callIR(cg, {setExpr->IRValue, cg.getPtr(element->IRValue)});
    }
    return setExpr->IRValue;
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
    cg.callStackPush();

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
    dArray->getAddFunc()->callIR(cg, {newArr.IRValue, cg.getPtr(v)});

    // Increment
    const auto inc = cg.builder.CreateAdd(iValue, cg.usize(1));
    cg.builder.CreateStore(inc, iPtr);
    cg.builder.CreateBr(condBlock);

    // End func
    cg.startBlock(exitBlock);
    cg.callPopStack(func->funcType->name);
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
    cg.callStackPush();

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
    cg.callPopStack(func->funcType->name);
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
