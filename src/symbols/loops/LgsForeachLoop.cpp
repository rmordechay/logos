#include "loops/LgsForeachLoop.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "stmts/LgsStmtsBlock.h"
#include "types/LgsDArray.h"
#include "types/LgsIterator.h"
#include "types/LgsMap.h"

void LgsForeachLoop::createIRLoop(LgsCodeGen* codeGen) {
    initIndex(codeGen);
    codeGen->branchAndStartBlock(IRCondBlock);
    const auto iterable = iterExpr->type->asIterable();
    if (iterable->asMap()) { // With iterator
        LgsIterator iterator = iterExpr->toIterator();
        iterator.initIterator(codeGen);
        codeGen->builder.CreateCondBr(iterator.hasNext(codeGen), IRBodyBlock, IRExitBlock);
        codeGen->startBlock(IRBodyBlock);
        iterPtr = iterExpr->getIRValue(codeGen);
        setMapIterVars(codeGen, iterator);
    } else { // Without iterator
        auto iValue = loadIndex(codeGen);
        const auto loopEnd = iterable->IRLength(codeGen, iterExpr);
        if (loopEnd->getType()->isIntegerTy(64)) {
            iValue = codeGen->builder.CreateSExt(iValue, codeGen->i64Ty());
        }
        const auto condition = codeGen->builder.CreateICmpSLT(iValue, loopEnd);
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
    stmtsBlock->createIRValue(codeGen);
}

void LgsForeachLoop::setStrIterVars(LgsCodeGen* codeGen, const LgsStr* str) const {
    const auto iValue = loadIndex(codeGen);
    const auto gep = codeGen->builder.CreateGEP(str->getIRBaseType(codeGen), iterPtr, {codeGen->i32Zero(), iValue});
    const auto load = codeGen->builder.CreateLoad(codeGen->i8Ty(), gep);
    if (withIndex) {
        loopVars[0]->setIRValue(iValue);
    }
    loopVars[0 + withIndex]->setIRValue(load);
}

void LgsForeachLoop::setArrIterVars(LgsCodeGen* codeGen, LgsDArray* arr) const {
    const auto iValue = loadIndex(codeGen);
    if (arr->asSArray()) {
        const auto gep = codeGen->builder.CreateGEP(arr->getIRType(codeGen), iterPtr, {codeGen->i32Zero(), iValue});
        if (withIndex) {
            loopVars[0]->setIRValue(iValue);
        }
        loopVars[0 + withIndex]->setIRValue(gep);
    } else {
        if (withIndex) {
            loopVars[0]->setIRValue(iValue);
        }
        const auto element = arr->getFunc.callIR(codeGen, {iterPtr, iValue});
        loopVars[0 + withIndex]->setIRValue(element);
    }
}

void LgsForeachLoop::setMapIterVars(LgsCodeGen* codeGen, const LgsIterator& iterator) const {
    const auto next = iterator.next(codeGen);
    const auto entryType = codeGen->getStructType({codeGen->ptrTy(), codeGen->ptrTy()}, "MapEntry");
    const auto keyGEP = codeGen->builder.CreateStructGEP(entryType, next, 0);
    const auto valueGEP = codeGen->builder.CreateStructGEP(entryType, next, 1);
    if (withIndex) {
        const auto iValue = loadIndex(codeGen);
        loopVars[0]->setIRValue(iValue);
    }
    loopVars[0 + withIndex]->setIRValue(keyGEP);
    loopVars[1 + withIndex]->setIRValue(valueGEP);
}

LgsForeachLoop::~LgsForeachLoop() {
    if (iterExpr) {
        delete iterExpr;
    }
    if (stmtsBlock) {
        delete stmtsBlock;
    }
}
