#include "loops/LgsForeachLoop.h"
#include "configs/LgsDefinitions.h"
#include "exprs/unary/LgsHashMap.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsDArray.h"
#include "types/LgsIterator.h"
#include "types/LgsMap.h"

Value* LgsForeachLoop::loopStart(LgsCodeGen* codeGen) {
    return codeGen->i64Zero();
}

Value* LgsForeachLoop::loopEnd(LgsCodeGen* codeGen) {
    const auto iterable = iterExpr->type->asIterable();
    return iterable->getLoopLength(codeGen, iterExpr);
}

void LgsForeachLoop::initIRLoop(LgsCodeGen* codeGen) {
    IRCondBlock = codeGen->createBlock(BLOCK_NAME_LOOP_COND);
    IRBodyBlock = codeGen->createBlock(BLOCK_NAME_LOOP_BODY);
    IRExitBlock = codeGen->createBlock(BLOCK_NAME_LOOP_EXIT);

    const auto iterable = iterExpr->type->asIterable();
    // With iterator
    if (iterable->asMap()) {
        LgsIterator iterator = iterExpr->toIterator();
        iterator.initIterator(codeGen);
        initIPtr(codeGen);
        codeGen->builder.CreateCondBr(iterator.hasNext(codeGen), IRBodyBlock, IRExitBlock);
        codeGen->startBlock(IRBodyBlock);
        iterPtr = iterExpr->getIRValue(codeGen);
        setMapIterVars(codeGen, iterator);
        return;
    }

    // Without iterator
    initIPtr(codeGen);
    const auto iValue = codeGen->builder.CreateLoad(codeGen->i64Ty(), iPtr);
    const auto upperBound = codeGen->builder.CreateZExt(loopEnd(codeGen), codeGen->i64Ty());
    const auto condition = codeGen->builder.CreateICmpSLT(iValue, upperBound);
    codeGen->builder.CreateCondBr(condition, IRBodyBlock, IRExitBlock);
    codeGen->startBlock(IRBodyBlock);
    iterPtr = iterExpr->getIRValue(codeGen);
    if (const auto str = iterable->asStr()) {
        setStrIterVars(codeGen, str);
    } else if (const auto arr = iterable->asDArray()) {
        setArrIterVars(codeGen, arr);
    } else {
        assert(0);
    }
}

void LgsForeachLoop::IRLoopPrologue(LgsCodeGen* codeGen) const {
    const auto iValue = codeGen->builder.CreateLoad(codeGen->i64Ty(), iPtr);
    const auto inc = codeGen->builder.CreateAdd(iValue, codeGen->i64(1));
    codeGen->builder.CreateStore(inc, iPtr);
    codeGen->builder.CreateBr(IRCondBlock);
}

void LgsForeachLoop::initIPtr(LgsCodeGen* codeGen) {
    iPtr = codeGen->builder.CreateAlloca(codeGen->i64Ty(), nullptr);
    codeGen->builder.CreateStore(loopStart(codeGen), iPtr);
    codeGen->builder.CreateBr(IRCondBlock);
    codeGen->startBlock(IRCondBlock);
}

void LgsForeachLoop::setStrIterVars(LgsCodeGen* codeGen, LgsStr* str) const {
    const auto i = codeGen->builder.CreateLoad(codeGen->i64Ty(), iPtr);
    const auto gep = codeGen->builder.CreateGEP(str->getIRType(codeGen), iterPtr, {codeGen->i32Zero(), i});
    const auto load = codeGen->builder.CreateLoad(codeGen->i8Ty(), gep);
    if (withIndex) {
        loopVars[0]->setIRValue(loadIPtr(codeGen));
    }
    loopVars[0 + withIndex]->setIRValue(load);
}

void LgsForeachLoop::setArrIterVars(LgsCodeGen* codeGen, LgsDArray* arr) const {
    if (arr->asSArray()) {
        const auto i = codeGen->builder.CreateLoad(codeGen->i64Ty(), iPtr);
        const auto gep = codeGen->builder.CreateGEP(arr->getIRType(codeGen), iterPtr, {codeGen->i32Zero(), i});
        if (withIndex) {
            loopVars[0]->setIRValue(loadIPtr(codeGen));
        }
        loopVars[0 + withIndex]->setIRValue(gep);
    } else {
        const auto iValue = loadIPtr(codeGen);
        if (withIndex) {
            loopVars[0]->setIRValue(iValue);
        }
        const auto v = arr->getFunc.callIR(codeGen, {iterPtr, iValue});
        loopVars[0 + withIndex]->setIRValue(codeGen->builder.CreateLoad(arr->getIRType(codeGen), v));
    }
}

void LgsForeachLoop::setMapIterVars(LgsCodeGen* codeGen, const LgsIterator& iterator) const {
    const auto next = iterator.next(codeGen);
    const auto entryType = codeGen->getIRStructType("MapEntry", {codeGen->ptrTy(), codeGen->ptrTy()});
    const auto keyGEP = codeGen->builder.CreateStructGEP(entryType, next, 0);
    const auto valueGEP = codeGen->builder.CreateStructGEP(entryType, next, 1);
    if (withIndex) {
        loopVars[0]->setIRValue(loadIPtr(codeGen));
    }
    loopVars[0 + withIndex]->setIRValue(keyGEP);
    loopVars[1 + withIndex]->setIRValue(valueGEP);
}

LoadInst* LgsForeachLoop::loadIPtr(LgsCodeGen* codeGen) const {
    return codeGen->builder.CreateLoad(codeGen->i64Ty(), iPtr);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
    if (stmtsBlock) {
        delete stmtsBlock;
    }
}
