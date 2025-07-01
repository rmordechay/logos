#include "loops/LgsForeachLoop.h"
#include "data/LgsDefinitions.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "stmts/LgsStmtBlock.h"
#include "types/LgsArray.h"
#include "types/LgsIterator.h"
#include "types/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsModule* runtime) {
    return runtime->builder.getInt64(0);
}

Value* LgsForeachLoop::loopEnd(LgsModule* runtime) {
    const auto iterable = iterExpr->type->asIterable();
    return iterable->getLoopLength(runtime, iterExpr);
}

void LgsForeachLoop::initIPtr(LgsModule* runtime)
{
    iPtr = runtime->builder.CreateAlloca(runtime->builder.getInt64Ty(), nullptr);
    runtime->builder.CreateStore(loopStart(runtime), iPtr);
    runtime->builder.CreateBr(IRCondBlock);
    startBlock(runtime, IRCondBlock);
}

void LgsForeachLoop::initIRLoop(LgsModule* runtime) {
    IRCondBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_CONDITION);
    IRBodyBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_BODY);
    IRExitBlock = BasicBlock::Create(runtime->context, LOGOS_LOOP_EXIT);

    const auto iterable = iterExpr->type->asIterable();
    // With iterator
    if (iterable->asMap()) {
        LgsIterator iterator = iterExpr->toIterator();
        iterator.initIterator(runtime);
        initIPtr(runtime);
        runtime->builder.CreateCondBr(iterator.hasNext(runtime), IRBodyBlock, IRExitBlock);
        startBlock(runtime, IRBodyBlock);
        iterPtr = iterExpr->getIRValue(runtime);
        setMapIterVars(runtime, iterator);
        return;
    }

    // Without iterator
    setLoopCondition(runtime);
    startBlock(runtime, IRBodyBlock);
    iterPtr = iterExpr->getIRValue(runtime);
    if (const auto str = iterable->asStr()) {
        setStrIterVars(runtime, str);
    } else if (const auto arr = iterable->asArray()) {
        setArrIterVars(runtime, arr);
    } else {
        assert(0);
    }
}

void LgsForeachLoop::exitIRLoop(LgsModule* runtime) const {
    // Increment loop variable
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
    const auto inc = runtime->builder.CreateAdd(iValue, runtime->builder.getInt64(1));
    runtime->builder.CreateStore(inc, iPtr);
    runtime->builder.CreateBr(IRCondBlock);
    startBlock(runtime, IRExitBlock);
}

void LgsForeachLoop::setStrIterVars(LgsModule* runtime, LgsStr* str) const {
    if (str->isStatic) {
        const auto i = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
        const auto gep = runtime->builder.CreateGEP(str->getIRType(runtime->context), iterPtr, {runtime->builder.getInt32(0), i});
        const auto load = runtime->builder.CreateLoad(runtime->builder.getInt8Ty(), gep);
        if (withIndex) {
            loopVars[0]->setIRValue(loadIPtr(runtime));
        }
        loopVars[0 + withIndex]->setIRValue(load);
    } else {
        assert(0);
    }
}

void LgsForeachLoop::setArrIterVars(LgsModule* runtime, LgsArray* arr) const {
    if (arr->isStatic) {
        const auto i = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
        const auto gep = runtime->builder.CreateGEP(arr->getIRType(runtime->context), iterPtr, {runtime->builder.getInt32(0), i});
        if (withIndex) {
            loopVars[0]->setIRValue(loadIPtr(runtime));
        }
        loopVars[0 + withIndex]->setIRValue(gep);
    } else {
        const auto iValue = loadIPtr(runtime);
        if (withIndex) {
            loopVars[0]->setIRValue(iValue);
        }
        const auto v = arr->getFunc.callIR(runtime, {iterPtr, iValue});
        loopVars[0 + withIndex]->setIRValue(runtime->builder.CreateLoad(arr->getIRType(runtime->context), v));
    }
}

void LgsForeachLoop::setMapIterVars(LgsModule* runtime, const LgsIterator& iterator) const {
    const auto next = iterator.next(runtime);
    const auto entryType = getIRStructType(runtime->context, "MapEntry", {ptrTy(runtime->context), ptrTy(runtime->context)});
    const auto keyGEP = runtime->builder.CreateStructGEP(entryType, next, 0);
    const auto valueGEP = runtime->builder.CreateStructGEP(entryType, next, 1);
    if (withIndex) {
        loopVars[0]->setIRValue(loadIPtr(runtime));
    }
    loopVars[0 + withIndex]->setIRValue(keyGEP);
    loopVars[1 + withIndex]->setIRValue(valueGEP);
}

void LgsForeachLoop::setLoopCondition(LgsModule* runtime) {
    initIPtr(runtime);
    const auto iValue = runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
    const auto upperBound = runtime->builder.CreateZExt(loopEnd(runtime), runtime->builder.getInt64Ty());
    const auto condition = runtime->builder.CreateICmpSLT(iValue, upperBound);
    runtime->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);
}

LoadInst* LgsForeachLoop::loadIPtr(LgsModule* runtime) const {
    return runtime->builder.CreateLoad(runtime->builder.getInt64Ty(), iPtr);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
    if (stmtBlock) {
        delete stmtBlock;
    }
}
