#include "codegen/LgsCgFile.h"

#include <llvm/IR/Module.h>
#include <__ostream/basic_ostream.h>
#include <_stdlib.h>
#include <_string.h>
#include <assert.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/Twine.h>
#include <llvm/IR/Argument.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Intrinsics.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <sstream>
#include <unordered_set>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "builtins/LgsSys.h"
#include "exprs/LgsArrayExpr.h"
#include "files/LgsInterfaceFile.h"
#include "files/LgsObjectFile.h"
#include "stmts/LgsField.h"
#include "stmts/LgsReturn.h"
#include "exprs/LgsBinaryExpr.h"
#include "exprs/LgsCast.h"
#include "exprs/LgsEnvVar.h"
#include "exprs/LgsFuncCall.h"
#include "exprs/LgsInstance.h"
#include "exprs/LgsIterIndex.h"
#include "exprs/LgsPostfixExpr.h"
#include "exprs/LgsPrefixExpr.h"
#include "exprs/LgsSelection.h"
#include "exprs/LgsTernaryExpr.h"
#include "exprs/LgsVariable.h"
#include "exprs/LgsVectorExpr.h"
#include "exprs/constants/LgsFloatConst.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsEnum.h"
#include "files/LgsMainFile.h"
#include "files/LgsTestFile.h"
#include "funcs/LgsMainFunc.h"
#include "logos/LgsAppConfigs.h"
#include "logos/LgsPaths.h"
#include "stmts/LgsBreak.h"
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
#include "exprs/LgsMatrixExpr.h"
#include "exprs/LgsMetaSelection.h"
#include "exprs/LgsNullableExpr.h"
#include "exprs/constants/LgsCharConst.h"
#include "types/LgsNullable.h"
#include "types/LgsEnumField.h"
#include "LgsBinaryTokens.h"
#include "LgsDefinitions.h"
#include "LgsSymbol.h"
#include "LgsSymbolTable.h"
#include "LgsType.h"
#include "LgsValue.h"
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsHashMap.h"
#include "exprs/constants/LgsIntConst.h"
#include "files/LgsFile.h"
#include "funcs/LgsFunc.h"
#include "funcs/LgsParam.h"
#include "loops/LgsMetaVar.h"
#include "stmts/LgsContinue.h"
#include "stmts/LgsStmt.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsFuncType.h"
#include "types/LgsInterface.h"
#include "types/LgsObject.h"
#include "types/iterables/LgsIterable.h"
#include "types/iterables/LgsMap.h"
#include "types/iterables/LgsStr.h"

namespace llvm {
class BasicBlock;
class Type;
}

bool LgsCgFile::generateSrcFile(LgsFile* file, const LgsPaths& paths) {
    visitExternalSymbols(file);
    if (const auto mainFile = file->asMainFile()) {
        visitMainFile(mainFile);
    } else if (const auto objFile = file->asObjectFile()) {
        if (objFile->obj->isSingleton) return true;
        visitObject(objFile->obj);
    } else if (const auto interfaceFile = file->asInterfaceFile()) {
        visitInterface(interfaceFile->interface);
    } else if (const auto testFile = file->asTestFile()) {
        visitTestFile(testFile);
    }
    if (appConfigs->debugMode) cg.finalizeDebugger(paths.buildDir);
    return cg.writeIRModule(paths, appConfigs->optLevel);
}

void LgsCgFile::visitMainFile(LgsMainFile* mainFile) {
    for (const auto varDec : mainFile->varDecs) {
        visitConstant(varDec->expr);
        varDec->IRValue = varDec->expr->IRValue;
    }
    for (const auto interface : mainFile->interfaces) {
        visitInterface(interface);
    }
    for (const auto object : mainFile->objects) {
        if (object->isSingleton) continue;
        visitObject(object);
    }
    for (const auto& [name, func] : mainFile->funcs) {
        if (const auto mainFunc = dynamic_cast<LgsMainFunc*>(func)) {
            visitMainFunc(mainFunc);
        } else {
            visitFunc(func);
        }
    }
}

void LgsCgFile::visitInterface(const LgsInterface* interface) {
    for (const auto& [_, method] : interface->methods) {
        if (!method->stmtsBlock) continue;
        visitFunc(method);
    }
}

void LgsCgFile::visitTestFile(const LgsTestFile* testFile) {
    for (const auto& func : testFile->funcs) {
        visitFunc(func);
    }
    for (const auto& test : testFile->tests) {
        visitFunc(test);
    }
}

void LgsCgFile::visitObject(LgsObject* obj) {
    if (!obj->typeParams.empty()) return;
    for (const auto& [_, method] : obj->methods) {
        visitFunc(method);
    }
}

void LgsCgFile::visitMainFunc(LgsMainFunc* func) {
    const auto savedIP =  cg.builder.saveIP();
    createPrologue(func);
    initMainArgs(func);
    visitStmtsBlock(func->stmtsBlock);
    createEpilogue(func, savedIP);
}

void LgsCgFile::visitFunc(LgsFunc* func) {
    if (!func->funcType->typeParams.empty()) return;
    if (!func->stmtsBlock) return;
    const auto ft = func->funcType;
    const auto savedIP =  cg.builder.saveIP();
    createPrologue(func);
    visitStmtsBlock(func->stmtsBlock);
    if (ft->isVariadic) {
        cg.callIntrinsics(Intrinsic::vaend, {cg.ptrTy()}, {ft->params.back().IRValue});
    }
    createEpilogue(func, savedIP);
}

void LgsCgFile::visitExternalSymbols(LgsFile* file) {
    for (auto [name, symbol] : file->symbolTable.symbols) {
        if (symbol.symbolType == VAR_DEC && symbol.isExternal) {
            visitConstant(symbol.varDec->expr);
            symbol.varDec->IRValue = symbol.varDec->expr->IRValue;
        }
    }
}

void LgsCgFile::visitStmt(LgsStmt* stmt) {
    if (const auto ifStmt = stmt->asIfStmt()) visitIfStmt(ifStmt);
    else if (const auto pattern = stmt->asSwitch()) visitSwitch(pattern);
    else if (const auto varDec = stmt->asVarDec()) visitVarDec(varDec);
    else if (const auto loopStmt = stmt->asLoop()) visitLoop(loopStmt);
    else if (const auto coroutine = stmt->asCoroutine()) visitCoroutine(coroutine);
    else if (const auto deferStmt = stmt->asDefer()) visitDeferStmt(deferStmt);
    else if (const auto assignment = stmt->asAssignment()) visitAssignment(assignment);
    else if (const auto ioStmt = stmt->asIOStmt()) visitIOStmt(ioStmt);
    else if (const auto returnStmt = stmt->asReturn()) visitReturnStmt(returnStmt);
    else if (const auto breakStmt = stmt->asBreak()) visitBreakStmt(breakStmt);
    else if (const auto continueStmt = stmt->asContinue()) visitContinueStmt(continueStmt);
}

void LgsCgFile::visitStmtsBlock(const LgsStmtsBlock* stmtsBlock) {
    if (!stmtsBlock) return;
    for (const auto& stmt : stmtsBlock->stmts) {
        switch (stmt.wrapperType) {
        case LgsStmtWrapper::WrapperType::Object:
            visitObject(stmt.obj);
            break;
        case LgsStmtWrapper::WrapperType::Stmt:
            visitStmt(stmt.stmt);
            if (appConfigs->debugMode) stmt.stmt->setDebugValue(cg);
            break;
        case LgsStmtWrapper::WrapperType::Expr:
            visitExpr(stmt.expr);
            if (appConfigs->debugMode) stmt.expr->setDebugValue(cg);
            break;
        }
    }
}

void LgsCgFile::visitLoop(LgsForLoop* loop) {
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
    cg.startBlock(loop->IRExitBlock);
}

void LgsCgFile::visitRangeLoop(LgsRangeLoop* loop) {
    visitExpr(loop->startRange);
    visitExpr(loop->endRange);
    loop->iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    const auto loopStart = cg.builder.CreateSExt(loop->loopStart(cg), cg.sizeTy());
    cg.store(loopStart, loop->iPtr);
    cg.builder.CreateBr(loop->IRCondBlock);

    // Condition
    cg.startBlock(loop->IRCondBlock);
    const auto loopEnd = loop->loopEnd(cg);
    const auto condition = cg.builder.CreateICmpSLT(loop->loadIndex(cg), loopEnd);
    cg.builder.CreateCondBr(condition, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock);
    if (!loop->loopVars.empty()) {
        loop->loopVars[0]->IRValue = loop->iPtr;
    }
}

void LgsCgFile::visitForeachLoop(LgsForeachLoop* loop) {
    visitExpr(loop->iterExpr);
    const auto indexTy = cg.sizeTy();
    loop->iPtr = cg.allocaAndStore(indexTy, cg.zeroSize());
    if (loop->iterExpr->type->asMap()) {
        loop->iteratorCounter = cg.allocaAndStore(cg.sizeTy(), cg.zeroSize());
    }

    // Condition
    cg.branchAndStartBlock(loop->IRCondBlock);
    const auto cond = cg.builder.CreateICmpSLT(loop->loadIndex(cg), loop->loopEnd(cg));
    cg.builder.CreateCondBr(cond, loop->IRBodyBlock, loop->IRExitBlock);

    // Body
    cg.startBlock(loop->IRBodyBlock);
    const auto iterable = loop->iterExpr->type->asIterable();
    iterable->setLoopIRVars(cg, loop);
}

void LgsCgFile::visitInfiniteLoop(const LgsInfiniteLoop* loop) {
    cg.branchAndStartBlock(loop->IRBodyBlock);
}

void LgsCgFile::visitLoopMetaVar(LgsMetaVar* metaVar) {
    const auto loop = metaVar->forLoop;
    const auto iValue = loop->loadIndex(cg);
    switch (metaVar->varType) {
    case FOR_I: {
        metaVar->IRValue = iValue;
        break;
    }
    case FOR_IS_FIRST: {
        metaVar->IRValue = cg.builder.CreateICmpEQ(iValue, loop->loopStart(cg));
        break;
    }
    case FOR_IS_LAST: {
        const auto decremented = cg.builder.CreateSub(loop->loopEnd(cg), cg.usize(1));
        metaVar->IRValue = cg.builder.CreateICmpEQ(iValue, decremented);
        break;
    }
    case FOR_ELEMENT:
        metaVar->IRValue = loop->loopVars.front()->expr->loadIRPtr(cg);
        break;
    }
}

void LgsCgFile::visitWhileLoop(const LgsWhileLoop* loop) {
    cg.builder.CreateBr(loop->IRCondBlock);
    cg.startBlock(loop->IRCondBlock);
    visitExpr(loop->condExpr);
    cg.builder.CreateCondBr(loop->condExpr->IRValue, loop->IRBodyBlock, loop->IRExitBlock);
    cg.startBlock(loop->IRBodyBlock);
}

void LgsCgFile::visitVarDec(LgsVarDec* varDec) {
    if (varDec->type->asFuncType()) {
        visitExpr(varDec->expr);
        varDec->IRValue = varDec->expr->IRValue;
    } else {
        const auto allocTy = varDec->type->isHeap ? cg.ptrTy() : varDec->type->getIRType(cg);
        varDec->IRValue = cg.builder.CreateAlloca(allocTy);
        varDec->expr->pointee = varDec->IRValue;
        visitExpr(varDec->expr);
        cg.store(varDec->expr->IRValue, varDec->IRValue);
    }
    varDec->IRValue->setName(varDec->name);
    assert(varDec->IRValue);
}

void LgsCgFile::visitAssignment(const LgsAssignment* assignment) {
    Value* lv;
    Value* rv;
    LgsType* lt;
    if (assignment->binaryExpr) {
        visitBinaryExpr(assignment->binaryExpr, false);
        visitExpr(assignment->binaryExpr->left, true);
        lv = assignment->binaryExpr->left->IRValue;
        rv = assignment->binaryExpr->IRValue;
        lt = assignment->binaryExpr->left->type;
    } else {
        const auto left = assignment->left;
        const auto right = assignment->right;
        lt = assignment->left->type;
        if (const auto iterIndex = left->asIterIndex()) {
            const auto iterable = iterIndex->baseExpr->type->asIterable();
            visitIterIndex(iterIndex, !iterable->isStatic);
            if (!iterable->isStatic) {
                right->pointee = iterIndex->IRValue;
                visitExpr(right);
                iterable->addIRElement(cg, iterIndex->baseExpr->IRValue, iterIndex->index.from->IRValue, right->IRValue);
                return;
            }
        } else {
            visitExpr(left, true);
        }
        right->pointee = left->IRValue;
        visitExpr(right);
        lv = left->pointee ? left->pointee : left->IRValue;
        rv = right->IRValue;
    }
    if (lt->isHeap && !lt->asNullable()) {
        rv = cg.moveValue(lt->getBaseName(), rv, cg.loadSize(cg.loadPtr(lv)));
    }
    cg.store(rv, lv);
}

void LgsCgFile::visitIfStmt(LgsIfStmt* ifStmt) {
    if (ifStmt->macroTrueBlock) {
        return visitStmtsBlock(ifStmt->macroTrueBlock);
    }
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

void LgsCgFile::visitSimpleIf(LgsIfStmt* ifStmt) {
    visitExpr(ifStmt->ifCond);
    const auto IRBlockIfTrue = cg.createBlock(BLOCK_TRUE);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_EXIT);
    cg.builder.CreateCondBr(ifStmt->ifCond->IRValue, IRBlockIfTrue, ifStmt->IRExitBlock);
    cg.startBlock(IRBlockIfTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock);
}

void LgsCgFile::visitIfWithElse(LgsIfStmt* ifStmt) {
    const auto IRBlockTrue = cg.createBlock(BLOCK_TRUE);
    const auto IRBlockExit = cg.createBlock(BLOCK_EXIT);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_FALSE);

    // if block
    visitExpr(ifStmt->ifCond);
    const auto ifCondIR = ifStmt->ifCond->IRValue;
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockExit);
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branch(ifStmt->IRExitBlock);

    // else block
    cg.startBlock(IRBlockExit);
    visitStmtsBlock(ifStmt->elseBlock);
    cg.branchAndStartBlock(ifStmt->IRExitBlock);
}

void LgsCgFile::visitElseIf(LgsIfStmt* ifStmt) {
    auto IRBlockTrue = cg.createBlock(BLOCK_TRUE);
    auto IRBlockElseIfCheck = cg.createBlock(BLOCK_ELSE_IF_CHECK);
    const auto IRBlockExit = cg.createBlock(BLOCK_EXIT);
    ifStmt->IRExitBlock = cg.createBlock(BLOCK_FALSE);

    // if block
    visitExpr(ifStmt->ifCond);
    const auto ifCondIR = ifStmt->ifCond->IRValue;
    cg.builder.CreateCondBr(ifCondIR, IRBlockTrue, IRBlockElseIfCheck);
    cg.startBlock(IRBlockTrue);
    visitStmtsBlock(ifStmt->ifBlock);
    cg.branch(ifStmt->IRExitBlock);

    for (size_t i = 0; i < ifStmt->elseIfs.size(); ++i) {
        const auto [expr, stmtBlock] = ifStmt->elseIfs[i];
        cg.startBlock(IRBlockElseIfCheck);
        visitExpr(expr);
        const auto elseIfCondIR = expr->IRValue;
        IRBlockTrue = cg.createBlock(BLOCK_ELSE_IF);
        if (i == ifStmt->elseIfs.size() - 1) {
            if (ifStmt->elseBlock) {
                cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockExit);
            } else {
                cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, ifStmt->IRExitBlock);
            }
        } else {
            IRBlockElseIfCheck = cg.createBlock(BLOCK_ELSE_IF_CHECK);
            cg.builder.CreateCondBr(elseIfCondIR, IRBlockTrue, IRBlockElseIfCheck);
        }
        cg.startBlock(IRBlockTrue);
        visitStmtsBlock(stmtBlock);
        cg.branch(ifStmt->IRExitBlock);
    }

    if (ifStmt->elseBlock) {
        cg.startBlock(IRBlockExit);
        visitStmtsBlock(ifStmt->elseBlock);
        cg.branch(ifStmt->IRExitBlock);
    }
    cg.startBlock(ifStmt->IRExitBlock);
}

void LgsCgFile::visitSwitch(LgsSwitch* switchStmt) {
    assert(switchStmt->cond);
    const auto cond = switchStmt->cond;
    visitExpr(cond);
    const auto exitBlock = cg.createBlock(BLOCK_EXIT);
    const auto defaultBlock = cg.createBlock(BLOCK_DEFAULT);
    const auto v = cond->type->hashValue(cg, cond->IRValue);
    const auto switchInst = cg.builder.CreateSwitch(v, defaultBlock, switchStmt->patterns.size());
    for (size_t i = 0; i < switchStmt->patterns.size(); ++i) {
        const auto patternBlock = cg.createBlock(BLOCK_CASE_PREFIX + std::to_string(i));
        const auto [expr, stmtsBlock] = switchStmt->patterns[i];
        const auto val = expr->hashConstValue(cg);
        const auto hashed = llvm::cast<ConstantInt>(val);
        switchInst->addCase(hashed, patternBlock);
        cg.startBlock(patternBlock);
        visitStmtsBlock(stmtsBlock);
        cg.builder.CreateBr(exitBlock);
    }
    if (switchStmt->elseBlock) {
        cg.startBlock(defaultBlock);
        visitStmtsBlock(switchStmt->elseBlock);
        cg.branch(exitBlock);
    }
    cg.startBlock(exitBlock);
}

void LgsCgFile::visitContinueStmt(const LgsContinue* continueStmt) {
    continueStmt->forLoop->incAndJumpToCond(cg);
}

void LgsCgFile::visitReturnStmt(LgsReturn* returnStmt) {
    const auto currentFunc = returnStmt->func;
    const auto ft = currentFunc->funcType;
    for (const auto ioStmt : returnStmt->ioStmts) {
        ioStmt->closeFunc->call(cg, {});
    }
    if (ft->rt->isVoid()) {
        cg.createRet();
    } else if (!currentFunc->returnStmts.empty()) {
        const auto expr = returnStmt->expr;
        if (ft->swapReturn) {
            expr->pointee = currentFunc->getIRFunc(cg)->getArg(ft->isMethod);
        }
        visitExpr(expr);
        if (ft->swapReturn) {
            const auto v = cg.load(expr->type->getIRType(cg), expr->IRValue);
            cg.store(v, expr->pointee);
        }
        returnStmt->parentBlock = cg.builder.GetInsertBlock();
        cg.builder.CreateBr(currentFunc->epilogue);
    }
}

void LgsCgFile::visitBreakStmt(const LgsBreak* breakStmt) {
    if (breakStmt->isBreakIf) {
        cg.builder.CreateBr(breakStmt->ifStmt->IRExitBlock);
    } else if (breakStmt->tag != "") {
        assert(0);
    } else {
        cg.builder.CreateBr(breakStmt->forLoop->IRExitBlock);
    }
}

void LgsCgFile::visitCoroutine(const LgsCoroutine* coroutine) {
    assert(0);
}

void LgsCgFile::visitDeferStmt(const LgsDeferStmt* defer) {
    const auto fc = defer->getAsFuncCall();
    if (fc->func->isLambda) {
        visitFunc(fc->func);
    }
    visitExpr(defer->expr);
    const auto ctxTy = getThunkCtxType(fc);
    const auto ctx = getThunkCtx(fc, ctxTy);
    const auto thunk = getThunkFunc(fc, ctxTy);
    cg.callRuntimeFunc("addDefer", cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {thunk, ctx});
}

void LgsCgFile::visitIOStmt(const LgsIOStmt* ioStmt) {
    const auto ioBlock = cg.createBlock("io_block");
    const auto exitBlock = cg.createBlock("io_exit_block");
    cg.branchAndStartBlock(ioBlock);
    visitExpr(ioStmt->varDec->expr);
    visitStmtsBlock(ioStmt->stmtsBlock);
    if (!cg.lastInstTerminator()) {
        ioStmt->closeFunc->call(cg, {});
    }
    cg.branchAndStartBlock(exitBlock);
}

void LgsCgFile::visitExpr(LgsExpr* expr, const bool assign) {
    if (!expr) return;
    if (const auto ternaryExpr = dynamic_cast<LgsTernaryExpr*>(expr)) {
        visitTernaryExpr(ternaryExpr);
    } else if (const auto binaryExpr = dynamic_cast<LgsBinaryExpr*>(expr)) {
        visitBinaryExpr(binaryExpr, assign);
    } else {
        if (const auto func = expr->asFunc()) visitFunc(func);
        else if (const auto charConst = expr->asCharConst()) visitCharConst(charConst);
        else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
        else if (const auto intConst = expr->asIntConst()) visitIntConst(intConst);
        else if (const auto floatConst = expr->asFloatConst()) visitFloatConst(floatConst);
        else if (const auto instance = expr->asInstance()) visitInstance(instance);
        else if (const auto funcCall = expr->asFuncCall()) visitFuncCall(funcCall);
        else if (const auto variable = expr->asVariable()) visitVariable(variable, assign);
        else if (const auto iterIndex = expr->asIterIndex()) visitIterIndex(iterIndex, assign);
        else if (const auto selection = expr->asSelection()) visitSelection(selection, assign);
        else if (const auto nullableExpr = expr->asNullableExpr()) visitNullableExpr(nullableExpr);
        else if (const auto metaSelection = expr->asMetaSelection()) visitMetaSelection(metaSelection);
        else if (const auto arrayExpr = expr->asArrayExpr()) visitArrayExpr(arrayExpr);
        else if (const auto hashMap = expr->asHashMap()) visitHashMap(hashMap);
        else if (const auto envVar = expr->asEnvVar()) visitEnvVar(envVar);
        else if (const auto postfixExpr = expr->asPostfixExpr()) visitPostfixExpr(postfixExpr);
        else if (const auto prefixExpr = expr->asPrefixExpr()) visitPrefixExpr(prefixExpr);
        else if (const auto vecExpr = expr->asVectorExpr()) visitVectorExpr(vecExpr);
        else if (const auto matrixExpr = expr->asMatrixExpr()) visitMatrixExpr(matrixExpr);
        else if (const auto loopMetaVar = expr->asLoopMetaVar()) visitLoopMetaVar(loopMetaVar);
        else if (const auto cast = expr->asCast()) visitCast(cast);
    }
}

void LgsCgFile::visitBinaryExpr(LgsBinaryExpr* binExpr, const bool assign) {
    assert(binExpr->type);
    const auto l = binExpr->left;
    const auto r = binExpr->right;
    visitExpr(l, assign);
    visitExpr(r, assign);
    const auto type = binExpr->type;
    switch (binExpr->op.opType) {
    case ADD: binExpr->IRValue = type->addIR(cg, binExpr); break;
    case SUB: binExpr->IRValue = type->subIR(cg, binExpr); break;
    case MUL: binExpr->IRValue = type->mulIR(cg, binExpr); break;
    case DIV: binExpr->IRValue = type->divIR(cg, binExpr); break;
    case MODULO: binExpr->IRValue = type->modIR(cg, binExpr); break;
    case POW: binExpr->IRValue = type->powIR(cg, binExpr); break;
    case BIT_AND: binExpr->IRValue = type->bitAndIR(cg, binExpr); break;
    case BIT_OR: binExpr->IRValue = type->bitOrIR(cg, binExpr); break;
    case BIT_XOR: binExpr->IRValue = type->bitXorIR(cg, binExpr); break;
    case LSHIFT: binExpr->IRValue = type->rshiftIR(cg, binExpr); break;
    case RSHIFT: binExpr->IRValue = type->lshiftIR(cg, binExpr); break;
    case EQ: binExpr->IRValue = eqIR(cg, l->IRValue, r->IRValue, l->type); break;
    case NE: binExpr->IRValue = neIR(cg, l->IRValue, r->IRValue, l->type); break;
    case LT: binExpr->IRValue = ltIR(cg, l->IRValue, r->IRValue, l->type); break;
    case GT: binExpr->IRValue = gtIR(cg, l->IRValue, r->IRValue, l->type); break;
    case GE: binExpr->IRValue = geIR(cg, l->IRValue, r->IRValue, l->type); break;
    case LE: binExpr->IRValue = leIR(cg, l->IRValue, r->IRValue, l->type); break;
    case AND: binExpr->IRValue = andIR(cg, {l->IRValue, r->IRValue}); break;
    case OR: binExpr->IRValue = orIR(cg, {l->IRValue, r->IRValue}); break;
    case IN: binExpr->IRValue = r->type->asIterable()->inIR(cg, r->IRValue, l->IRValue); break;
    case CROSS: binExpr->IRValue = crossIR(cg, binExpr->left->IRValue, binExpr->right->IRValue, type->asVec()); break;
    default: assert(0);
    }
}

void LgsCgFile::visitTernaryExpr(LgsTernaryExpr* ternaryExpr) {
    const auto cond = ternaryExpr->condExpr;
    const auto then = ternaryExpr->thenExpr;
    const auto else_ = ternaryExpr->elseExpr;
    visitExpr(cond);
    visitExpr(then);
    visitExpr(else_);
    ternaryExpr->IRValue = cg.builder.CreateSelect(cond->IRValue, then->IRValue, else_->IRValue);
}

void LgsCgFile::visitInstance(LgsInstance* instance) {
    const auto obj = instance->obj;
    visitObject(obj);
    if (obj->isExternal) {
        instance->IRValue = cg.builder.CreateAlloca(obj->getIRType(cg));
        assert(instance->args.empty());
        return;
    }

    const auto level = instance->getLevel(cg);
    instance->IRValue = obj->getIRZeroValue(cg, instance->pointee, level);

    // Args
    std::unordered_set<std::string> visited;
    for (const auto& arg : instance->args) {
        const auto name = arg.name;
        visited.insert(name);
        if (obj->getMethod(name)) {
            visitExpr(arg.expr);
            continue;
        }
        const auto field = obj->getField(name);
        if (!field) continue;
        arg.expr->pointee = field->getGEP(cg, instance->IRValue);
        visitExpr(arg.expr);
        cg.store(arg.expr->IRValue, arg.expr->pointee);
    }

    // Zero values
    for (const auto field : instance->obj->fields) {
        const auto fieldType = field->type;
        if (visited.contains(field->name) || fieldType->asEnum()) continue;
        const auto pointee = field->getGEP(cg, instance->IRValue);
        cg.store(field->type->getIRZeroValue(cg, pointee, level), pointee);
    }
}

void LgsCgFile::visitConstant(LgsExpr* expr) {
    if (const auto charConst = expr->asCharConst()) visitCharConst(charConst);
    else if (const auto strConst = expr->asStrConst()) visitStrConst(strConst);
    else if (const auto intConst = expr->asIntConst()) visitIntConst(intConst);
    else if (const auto floatConst = expr->asFloatConst()) visitFloatConst(floatConst);
    else assert(0);
}

void LgsCgFile::visitFloatConst(LgsFloatConst* floatConst) {
    if (floatConst->type->asFloat()) {
        floatConst->IRValue = cg.floatv(floatConst->value);
    } else if (floatConst->type->asDouble()) {
        floatConst->IRValue = cg.doublev(floatConst->value);
    } else {
        assert(0);
    }
}

void LgsCgFile::visitIntConst(LgsIntConst* intConst) {
    const auto ty = intConst->type;
    if (ty->asBool()) {
        intConst->IRValue = cg.i1(intConst->value);
    } else if (ty->asByte() || ty->asUByte() || ty->asChar()) {
        intConst->IRValue = cg.i8(intConst->value);
    } else if (ty->asShort() || ty->asUShort()) {
        intConst->IRValue = cg.i16(intConst->value);
    } else if (ty->asInt() || ty->asUInt()) {
        intConst->IRValue = cg.i32(intConst->value);
    } else if (ty->asLong() || ty->asULong()) {
        intConst->IRValue = cg.i64(intConst->value);
    } else if (ty->asSize()) {
        intConst->IRValue = cg.usize(intConst->value);
    } else if (ty->asFloat()) {
        intConst->IRValue = cg.floatv(intConst->value);
    } else if (ty->asDouble()) {
        intConst->IRValue = cg.doublev(intConst->value);
    } else {
        assert(0);
    }
}

void LgsCgFile::visitStrConst(LgsStrConst* strConst) {
    if (strConst->parts.empty()) {
        strConst->IRValue = cg.heapAllocType(LgsStr::name, cg.getString(strConst->value), cg.zeroSize());
        return;
    }
    std::vector<Value*> values;
    auto formatted = strConst->formatedStr;
    for (const auto part : strConst->parts) {
        visitExpr(part);
        LgsStrBuilder sb(cg);
        part->type->asIRText(sb, part->IRValue);
        values.push_back(sb.buffer);
        const auto pos = formatted.find(LGS_STR_FMT_PLACEHOLDER);
        if (pos != std::string::npos) {
            formatted.replace(pos, strlen(LGS_STR_FMT_PLACEHOLDER), "%s");
        }
    }
    strConst->IRValue = cg.heapAllocType(LgsStr::name, cg.callSnprintf(formatted, values), cg.zeroSize());
}

void LgsCgFile::visitCharConst(LgsCharConst* charConst) {
    charConst->IRValue = cg.i8(charConst->value);
}

void LgsCgFile::visitPrefixExpr(LgsPrefixExpr* prefixExpr) {
    visitExpr(prefixExpr->expr);
    const auto exprIRVal = prefixExpr->expr->IRValue;
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

void LgsCgFile::visitPostfixExpr(LgsPostfixExpr* postfixExpr) {
    const auto variable = postfixExpr->baseExpr->asVariable();
    assert(variable);
    visitVariable(variable, true);
    const auto baseExprType = postfixExpr->baseExpr->type->getIRType(cg);
    const auto baseValue = cg.load(baseExprType, postfixExpr->baseExpr->IRValue);
    const auto one = ConstantInt::get(baseExprType, 1, true);
    Value* newValue = nullptr;
    switch (postfixExpr->op) {
    case INC: {
        newValue = cg.builder.CreateAdd(baseValue, one);
        break;
    }
    case DEC: {
        newValue = cg.builder.CreateSub(baseValue, one);
        break;
    }
    }
    cg.store(newValue, postfixExpr->baseExpr->IRValue);
    postfixExpr->IRValue = newValue;
}

void LgsCgFile::visitVariable(LgsVariable* variable, const bool assign) {
    switch (variable->ref.symbolType) {
    case VAR_DEC: {
        const auto varDec = variable->ref.varDec;
        assert(variable->ref.varDec->IRValue);
        const auto obj = varDec->type->asObject();
        if (obj && obj->isSingleton) {
            variable->IRValue = cg.createGlobal(varDec->name, variable->type->getIRType(cg), nullptr);
        } else {
            variable->IRValue = varDec->IRValue;
            if (!assign) {
                variable->IRValue = variable->loadIRPtr(cg);
            }
        }
        break;
    }
    case PARAM:
        if (variable->ref.param->isSelf) {
            variable->IRValue = cg.currentFunc->getArg(0);
        } else {
            assert(variable->ref.param->IRValue);
            variable->IRValue = variable->ref.param->IRValue;
        }
        break;
    case FUNC:
        variable->IRValue = variable->ref.func->getIRFunc(cg);
        break;
    case FIELD:
        if (variable->ref.field->type->asEnum()) {
            variable->IRValue = cg.usize(variable->ref.field->index);
        } else {
            variable->IRValue = variable->pointee;
        }
        break;
    case OBJECT:
    case ENUM:
    case INTERFACE:
    case SUBTYPE:
        return;
    case UNKNOWN:
        break;
    }
    assert(variable->IRValue);
}

void LgsCgFile::visitIterIndex(LgsIterIndex* iterIndex, const bool assign) {
    const auto baseExpr = iterIndex->baseExpr;
    const auto iterable = baseExpr->type->asIterable();
    const auto from = iterIndex->index.from;
    const auto to = iterIndex->index.to;
    visitExpr(baseExpr);
    visitExpr(from);
    visitExpr(to);
    if (assign) return;
    if (to) {
        iterIndex->IRValue = iterIndex->getIRRangePtr(cg);
    } else {
        const auto baseExprValue = baseExpr->pointee ? baseExpr->pointee : baseExpr->IRValue;
        iterIndex->IRValue = iterable->getIRElement(cg, baseExprValue, from->IRValue);
        if (!iterable->isStatic) {
            iterIndex->IRValue = iterIndex->loadIRPtr(cg);
        }
    }
}

void LgsCgFile::visitSelection(LgsSelection* selection, const bool assign) {
    visitExpr(selection->exprs.front());
    const auto iterationCount = selection->exprs.size() - 1;
    for (size_t i = 0; i < iterationCount; ++i) {
        const auto parent = selection->exprs[i];
        const auto child = selection->exprs[i + 1];
        if (const auto var = child->asVariable()) {
            visitFieldSelection(var, parent);
            if (!assign || i != iterationCount - 1) {
                var->IRValue = var->loadIRPtr(cg);
            }
        } else if (const auto methodCall = child->asFuncCall()) {
            visitFuncCall(methodCall);
        } else if (const auto metaSelection = child->asMetaSelection()) {
            visitMetaSelection(metaSelection);
        } else if (const auto instance = child->asInstance()) {
            visitInstance(instance);
        } else {
            assert(0);
        }
    }
    selection->IRValue = selection->exprs.back()->IRValue;
}

void LgsCgFile::visitNullableExpr(LgsNullableExpr* expr) {
     const auto nullable = expr->type->asNullable();
    assert(nullable);
    visitExpr(expr->baseExpr);
    if (expr->isNull) {
        expr->IRValue = nullable->getIRZeroValue(cg, expr->pointee, expr->getLevel(cg));
    } else {
        if (nullable->passByRef) {
            expr->IRValue = expr->baseExpr->IRValue;
        } else {
            expr->IRValue = nullable->getIRZeroValue(cg, expr->pointee, expr->getLevel(cg));
            nullable->setIRFields(cg, expr->IRValue, expr->baseExpr->IRValue, cg.true_());
            expr->IRValue = expr->loadIRPtr(cg);
        }
    }
}

void LgsCgFile::visitFieldSelection(LgsVariable* var, const LgsExpr* parent) {
    const auto field = var->ref.field;
    const auto fieldType = field->type;
    // Function pointer
    if (var->ref.symbolType == FUNC) {
        var->IRValue = var->ref.func->getIRFunc(cg);
        return;
    }
    // Enum field
    if (const auto enumField = var->type->asEnumField()) {
        if (field->expr) {
            const auto g = field->expr->getAsConst(cg);
            const auto fieldTy = field->type->getIRType(cg);
            if (var->pointee) {
                var->IRValue = var->pointee;
                cg.storeField(fieldTy, var->IRValue, 0, cg.usize(enumField->index));
                cg.storeField(fieldTy, var->IRValue, 1, g);
            } else {
                var->IRValue = UndefValue::get(fieldTy);
                var->IRValue = cg.builder.CreateInsertValue(var->IRValue, cg.usize(enumField->index), 0);
                var->IRValue = cg.builder.CreateInsertValue(var->IRValue, g, 1);
            }
        } else {
            var->IRValue = cg.usize(enumField->index);
        }
        return;
    }
    // Enum
    if (const auto enum_ = var->type->asEnum()) {
        var->IRValue = cg.getString(enum_->name);
        return;
    }
    // Singleton
    if (parent->type->asObject()->isSingleton) {
        assert(0);
    }
    // Virtual fields
    if (field->isVirtual) {
        const auto ty = parent->type->getIRType(cg);
        const auto rttType = LgsInstance::loadRTType(cg, ty, parent->IRValue);
        var->IRValue = cg.getVField(rttType, parent->IRValue, cg.getString(field->name));
        return;
    }
    // Vector
    if (fieldType->asVec()) {
        createVecField(field, parent->IRValue);
    }
    var->IRValue = field->getGEP(cg, parent->IRValue);
}

void LgsCgFile::visitMetaSelection(LgsMetaSelection* metaSelection) {
    visitExpr(metaSelection->baseExpr);
    if (const auto fc = metaSelection->child->asFuncCall()) {
        visitFuncCall(fc);
        metaSelection->IRValue = fc->IRValue;
        return;
    }
    if (const auto var = metaSelection->child->asVariable()) {
        const auto field = var->ref.field;
        visitExpr(field->expr);
        metaSelection->IRValue = field->expr->IRValue;
        return;
    }
    assert(0);
}

void LgsCgFile::visitFuncCall(LgsFuncCall* funcCall) {
    if (funcCall->isMock) return;
    for (const auto& arg : funcCall->args) {
        if (arg.name == LGS_SELF) continue;
        visitExpr(arg.expr);
    }

    // Function pointer
    if (funcCall->ref.symbolType != UNKNOWN) {
        LgsType* type = nullptr;
        const LgsValue* value = nullptr;
        if (funcCall->ref.symbolType == PARAM) {
            type = funcCall->ref.param->type;
            value = funcCall->ref.param;
        } else if (funcCall->ref.symbolType == VAR_DEC) {
            type = funcCall->ref.varDec->type;
            value = funcCall->ref.varDec;
        }
        funcCall->func = new LgsFunc(type->asFuncType());
        funcCall->func->IRValue = value->IRValue;
    }
    assert(funcCall->func || funcCall->coroutine);
    const auto func = funcCall->func ? funcCall->func : funcCall->coroutine;
    const auto ft = func->funcType;
    assert(func->funcType->typeParams.empty());

    // Default params
    if (ft->hasDefaults && ft->params.size() > funcCall->args.size()) {
        for (size_t i = funcCall->args.size(); i < ft->params.size(); ++i) {
            visitExpr(ft->params[i].expr);
        }
    }

    // Virtual func call
    if (ft->isVirtual) {
        const auto self = funcCall->args.front().expr;
        const auto offset = cg.getTypeSize(cg.sizeTy());
        const auto rttType = cg.builder.CreatePtrAdd(self->IRValue, offset);
        const auto objType = loadRTTInfoExtra(cg, cg.loadPtr(rttType));
        func->IRValue = cg.getVFunc(objType, cg.getString(ft->name));
    }

    if (funcCall->coroutine || funcCall->isDeferred) return;
    if (ft->isMethod && !ft->hasSelf && !funcCall->args.front().expr->IRValue) {
        funcCall->args.front().expr->IRValue = cg.null();
    }
    funcCall->IRValue = func->call(cg, funcCall->args);
}

void LgsCgFile::visitArrayExpr(LgsArrayExpr* arrayExpr) {
    if (arrayExpr->type->asSArray()) {
        visitStaticArray(arrayExpr);
    } else if (arrayExpr->type->asDArray() || arrayExpr->type->asSet()) {
        visitDynamicArray(arrayExpr);
    } else {
        assert(0);
    }
}

void LgsCgFile::visitStaticArray(LgsArrayExpr* arrayExpr) {
    const auto sArr = arrayExpr->type->asSArray();
    const auto ty = sArr->getIRType(cg);
    arrayExpr->IRValue = sArr->getIRZeroValue(cg, arrayExpr->pointee, arrayExpr->getLevel(cg));
    if (arrayExpr->elements.empty()) {
        cg.store(ConstantAggregateZero::get(ty), arrayExpr->IRValue);
        return;
    }

    // Init with zero the remaining args that are not set by the user.
    if (arrayExpr->elements.size() < sArr->len) {
        cg.store(ConstantAggregateZero::get(ty), arrayExpr->IRValue);
    }

    for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
        const auto element = arrayExpr->elements[i];
        element->pointee = sArr->getIRElement(cg, arrayExpr->IRValue, cg.i32(i));
        visitExpr(element);
    }

    for (size_t i = 0; i < arrayExpr->elements.size(); ++i) {
        const auto element = arrayExpr->elements[i];
        cg.store(element->IRValue, element->pointee);
    }
}

void LgsCgFile::visitDynamicArray(LgsArrayExpr* arrayExpr) {
    for (const auto element : arrayExpr->elements) {
        visitExpr(element);
    }
    const auto dArr = arrayExpr->type->asDArray();
    arrayExpr->IRValue = dArr->getIRZeroValue(cg, arrayExpr->pointee, arrayExpr->getLevel(cg));
    for (const auto element : arrayExpr->elements) {
        dArr->addIRElement(cg, arrayExpr->IRValue, nullptr, element->IRValue);
    }
}

void LgsCgFile::visitVectorExpr(LgsVectorExpr* vecExpr) {
    const auto vecType = vecExpr->vecType;
    const auto ty = vecType->getIRType(cg);
    if (vecExpr->elements.empty()) {
        vecExpr->IRValue = vecType->getIRZeroValue(cg, vecExpr->pointee, vecExpr->getLevel(cg));
        cg.store(Constant::getNullValue(ty), vecExpr->pointee ? vecExpr->pointee : vecExpr->IRValue);
        return;
    }

    // Single scalar element
    if (vecExpr->elements.size() == 1 && vecExpr->elements.front()->type->isScalar()) {
        const auto element = vecExpr->elements.front();
        visitExpr(element);
        const auto newVec = cg.builder.CreateVectorSplat(vecType->dimVec, element->IRValue);
        if (vecExpr->pointee) {
            vecExpr->IRValue = vecExpr->pointee;
            cg.store(newVec, vecExpr->IRValue);
        } else {
            vecExpr->IRValue = cg.allocaAndStore(ty, newVec);
        }
        return;
    }

    // Multiple elements
    vecExpr->IRValue = vecExpr->vecType->getIRZeroValue(cg, vecExpr->pointee, vecExpr->getLevel(cg));
    if (vecExpr->sumArgsDim < vecType->dimVec) {
        cg.store(Constant::getNullValue(ty), vecExpr->pointee ? vecExpr->pointee : vecExpr->IRValue);
    }
    size_t index = 0;
    for (size_t i = 0; i < vecExpr->elements.size(); ++i) {
        const auto element = vecExpr->elements[i];
        element->pointee = vecType->getIRElement(cg, vecExpr->IRValue, cg.i32(index));
        visitExpr(element);
        cg.store(element->IRValue, element->pointee);
        if (const auto innerVec = element->type->asVec()) {
            index += innerVec->dimVec;
        } else {
            index++;
        }
    }
}

void LgsCgFile::visitMatrixExpr(LgsMatrixExpr* matExpr) {
    const auto matType = matExpr->matType;
    const auto ty = matType->getIRType(cg);
    if (matExpr->rows.empty()) {
        matExpr->IRValue = matType->getIRZeroValue(cg, matExpr->pointee, matExpr->getLevel(cg));
        cg.store(Constant::getNullValue(ty), matExpr->pointee);
        return;
    }
    matExpr->IRValue = matExpr->matType->getIRZeroValue(cg, matExpr->pointee, matExpr->getLevel(cg));
    cg.store(Constant::getNullValue(ty), matExpr->pointee ? matExpr->pointee : matExpr->IRValue);
    for (size_t i = 0; i < matExpr->rows.size(); ++i) {
        const auto row = matExpr->rows[i];
        const auto rowTy = row->type->getIRType(cg);
        row->pointee = cg.builder.CreateInBoundsGEP(rowTy, matExpr->IRValue, {cg.i32(i)});
        visitExpr(row);
        cg.store(row->loadIRPtr(cg), row->pointee);
    }
}

void LgsCgFile::visitHashMap(LgsHashMap* hashMap) {
    const auto map = hashMap->type->asMap();
    hashMap->IRValue = hashMap->type->getIRZeroValue(cg, hashMap->pointee, hashMap->getLevel(cg));
    for (const auto pair : hashMap->elements) {
        visitExpr(pair->key);
        visitExpr(pair->value);
        map->addIRElement(cg, hashMap->IRValue, pair->key->IRValue, pair->value->IRValue);
    }
}

void LgsCgFile::visitEnvVar(LgsEnvVar* envVar) {
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {cg.getString(envVar->name), cg.emptyStr()};
    const auto env = cg.callLgsFunc(LgsSys::name, "getEnv", cg.ptrTy(), params, IRArgs);
    envVar->IRValue = cg.heapAllocType(LgsStr::name, env, cg.currentLevel);
}

void LgsCgFile::visitCast(LgsCast* cast) {
    assert(cast->value);
    visitExpr(cast->value);
    cast->IRValue = cast->value->IRValue;
}

void LgsCgFile::createPrologue(LgsFunc* func) {
    if (appConfigs->debugMode) func->setDebugValue(cg);
    func->epilogue = cg.createBlock("epilogue");
    const auto ft = func->funcType;
    const auto IRFunc = func->getIRFunc(cg);
    if (func->isLambda) {
        func->IRValue = IRFunc;
    }
    cg.startFunc(IRFunc, ft->name == LGS_MAIN_FUNC);
    if (func->isTest) for (auto [_, then] : func->mocks) visitExpr(then);
    if (ft->isVariadic) {
        ft->params.back().IRValue = cg.builder.CreateAlloca(cg.ptrTy(), nullptr, "va_list");
        cg.callIntrinsics(Intrinsic::vastart, {cg.ptrTy()}, {ft->params.back().IRValue});
    }
}

void LgsCgFile::createEpilogue(const LgsFunc* func, const IRBuilderBase::InsertPoint& savedIP) {
    const auto ft = func->funcType;
    // Main func
    if (ft->name == LGS_MAIN_FUNC) {
        cg.createRet(cg.i32(EXIT_SUCCESS), true);

        return;
    }
    if (ft->isVariadic) {
        cg.callIntrinsics(Intrinsic::vaend, {cg.ptrTy()}, {ft->params.back().IRValue});
    }
    // No return
    if (ft->rt->isVoid()) {
        if (!cg.lastInstTerminator()) {
            cg.createRet();
        }
    } else { // With return
        auto& stmts = func->returnStmts;
        assert(!stmts.empty());
        cg.branchAndStartBlock(func->epilogue);
        if (ft->swapReturn) {
            cg.createRet();
        } else {
            const auto phi = cg.builder.CreatePHI(ft->rt->getStorageType(cg), stmts.size());
            for (const auto returnStmt : stmts) {
                phi->addIncoming(returnStmt->expr->IRValue, returnStmt->parentBlock);
            }
            if (ft->rt->isHeap) {
                cg.createRet(ft->rt->moveValue(cg, phi, cg.levelAbove()));
            } else {
                cg.createRet(phi);
            }
        }
    }
    cg.restoreFuncState(savedIP);
}

void LgsCgFile::initMainArgs(const LgsMainFunc* mainFunc) const {
    const auto ft = mainFunc->funcType;
    if (ft->params.empty()) return;
    const auto argsArray = ft->params.front().expr->asArrayExpr();
    const auto sArray = argsArray->type->asSArray();
    sArray->lengthExpr->IRValue = cg.currentFunc->getArg(0);
    argsArray->IRValue = cg.currentFunc->getArg(1);
    mainFunc->funcType->params[0].IRValue = argsArray->IRValue;
}

Type* LgsCgFile::getThunkCtxType(const LgsFuncCall* fc) {
    if (fc->args.empty()) return cg.ptrTy();
    std::vector<Value*> args;
    std::vector<Type*> types;
    std::stringstream strTypes;
    for (const auto& arg : fc->args) {
        types.push_back(arg.expr->type->getIRType(cg));
        strTypes << arg.expr->type->getName();
    }
    return cg.getStructType(types, "ThunkFunc_" + strTypes.str());
}

Value* LgsCgFile::getThunkCtx(const LgsFuncCall* fc, Type* ctxTy) {
    if (fc->args.empty()) return cg.null();
    const auto ctx = cg.builder.CreateAlloca(ctxTy);
    for (size_t i = 0; i < fc->args.size(); i++) {
        const auto v = fc->args[i].expr->IRValue;
        cg.storeField(ctxTy, ctx, i, v);
    }
    return ctx;
}

Function* LgsCgFile::getThunkFunc(const LgsFuncCall* fc, Type* ctxTy) {
    const auto funcName = fc->name + "Thunk";
    auto thunkFunc = cg.IRModule->getFunction(funcName);
    if (thunkFunc) return thunkFunc;
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy()});
    thunkFunc = cg.getFunc(funcName, ft, Function::PrivateLinkage);

    const auto savedIP =  cg.builder.saveIP();
    cg.startFunc(thunkFunc);
    for (size_t i = 0; i < fc->args.size(); i++) {
        const auto expr = fc->args[i].expr;
        expr->IRValue = cg.builder.CreateStructGEP(ctxTy, thunkFunc->arg_begin(), i);
        expr->IRValue = expr->loadIRPtr(cg);
    }
    fc->func->call(cg, fc->args);
    cg.createRet();
    cg.restoreFuncState(savedIP);
    return thunkFunc;
}

void LgsCgFile::createVecField(LgsField* field, Value* parent) {
    const auto vec = field->type->asVec();
    assert(vec);
    std::vector<int> mask(vec->dimVec);
    for (size_t i = 0; i < vec->dimVec; i++) {
        mask[i] = LgsVec::getComponentIndex(field->name[i]);
    }
    const auto vecType = field->type->getIRType(cg);
    field->IRValue = cg.builder.CreateAlloca(vecType);
    const auto parentTy = field->parentType->getIRType(cg);
    const auto l = cg.load(parentTy, parent);
    const auto newVec = cg.builder.CreateShuffleVector(l, UndefValue::get(parentTy), mask);
    cg.store(newVec, field->IRValue);
}

void LgsCgFile::getMapFunc(LgsFuncType* mapFunc) {
    const auto& iterableParam = mapFunc->params[0];
    const auto& cbParam = mapFunc->params[1];
    const auto iterable = iterableParam.type->asIterable();
    const auto funcName = mapFunc->getName();
    const auto ft = llvm::cast<FunctionType>(mapFunc->getIRType(cg));
    const auto cbFt = llvm::cast<FunctionType>(cbParam.type->getIRType(cg));

    const auto func = cg.getFunc(funcName, ft);
    const auto savedIP =  cg.builder.saveIP();
    cg.startFunc(func);
    const auto iter = func->getArg(0);
    const auto cb = func->getArg(1);

    LgsDArray dArr(iterable->baseType);
    LgsArrayExpr retArr(&dArr);
    retArr.IRValue = cg.heapAllocType(LgsDArray::name, dArr.baseType->getRTType(cg), cg.levelAbove());
    const auto len = iterable->lenIR(cg, iter);

    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto element = iterable->getIRElement(cg, iter, iValue);
        const auto loadElement = cg.load(iterable->baseType->getIRType(cg), element);
        const auto results = cg.builder.CreateCall(cbFt, cb, {loadElement});
        dArr.addIRElement(cg, retArr.IRValue, nullptr, results);
    });

    cg.createRet(retArr.IRValue);
    cg.restoreFuncState(savedIP);
}

void LgsCgFile::getFilterFunc(LgsFuncType* filterFunc) {
    const auto& iterableParam = filterFunc->params[0];
    const auto& cbParam = filterFunc->params[1];
    const auto iterable = iterableParam.type->asIterable();
    const auto funcName = filterFunc->getName();

    const auto ft = llvm::cast<FunctionType>(filterFunc->getIRType(cg));
    const auto cbFt = llvm::cast<FunctionType>(cbParam.type->getIRType(cg));
    const auto func = cg.getFunc(funcName, ft);
    const auto savedIP =  cg.builder.saveIP();
    cg.startFunc(func);

    const auto iter = func->getArg(0);
    const auto cb = func->getArg(1);

    LgsDArray dArr(iterable->baseType);
    LgsArrayExpr retArr(&dArr);
    retArr.IRValue = cg.heapAllocType(LgsDArray::name, dArr.baseType->getRTType(cg), cg.levelAbove());
    const auto len = iterable->lenIR(cg, iter);

    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto baseTy = iterable->baseType->getIRType(cg);
        const auto element = iterable->getIRElement(cg, iter, iValue);
        const auto loadElement = cg.load(baseTy, element);
        const auto results = cg.builder.CreateCall(cbFt, cb, {loadElement});
        cg.ifStmt(results, [&] {
            dArr.addIRElement(cg, retArr.IRValue, nullptr, cg.load(baseTy, element));
        });
    });

    cg.createRet(retArr.IRValue);
    cg.restoreFuncState(savedIP);
}

void LgsCgFile::getForeachFunc(LgsFuncType* forEachFunc) {
    const auto& iterableParam = forEachFunc->params[0];
    const auto& cbParam = forEachFunc->params[1];
    const auto iterable = iterableParam.type->asIterable();
    const auto funcName = forEachFunc->getName();

    const auto ft = llvm::cast<FunctionType>(forEachFunc->getIRType(cg));
    const auto cbFt = llvm::cast<FunctionType>(cbParam.type->getIRType(cg));
    const auto func = cg.getFunc(funcName, ft);
    const auto savedIP =  cg.builder.saveIP();
    cg.startFunc(func);

    const auto iter = func->getArg(0);
    const auto cb = func->getArg(1);

    const auto len = iterable->lenIR(cg, iter);
    cg.loop(len, [&](Value* iValue, BasicBlock*) {
        const auto element = iterable->getIRElement(cg, iter, iValue);
        const auto loadElement = cg.load(iterable->baseType->getIRType(cg), element);
        cg.builder.CreateCall(cbFt, cb, {loadElement});
    });

    cg.createRet();
    cg.restoreFuncState(savedIP);
}
