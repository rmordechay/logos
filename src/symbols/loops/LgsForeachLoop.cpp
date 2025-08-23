#include "loops/LgsForeachLoop.h"
#include "exprs/unary/LgsIterIndex.h"
#include "stmts/LgsVarDec.h"
#include "types/LgsDArray.h"
#include "exprs/unary/LgsIterator.h"
#include "types/LgsMap.h"

void LgsForeachLoop::setStrIterVars(LgsCodeGen& codeGen, const LgsStr* str) const {
    const auto iValue = loadIndex(codeGen);
    const auto gep = codeGen.builder.CreateGEP(str->getIRBaseType(&codeGen), iterPtr, {codeGen.i32Zero(), iValue});
    const auto load = codeGen.builder.CreateLoad(codeGen.i8Ty(), gep);
    if (withIndex) {
        loopVars[0]->setIRValue(iValue);
    }
    loopVars[0 + withIndex]->setIRValue(load);
}

void LgsForeachLoop::setArrIterVars(LgsCodeGen& codeGen, LgsDArray* arr) const {
    const auto iValue = loadIndex(codeGen);
    if (arr->asSArray()) {
        const auto gep = codeGen.builder.CreateGEP(arr->getIRType(codeGen), iterPtr, {codeGen.i32Zero(), iValue});
        if (withIndex) {
            loopVars[0]->setIRValue(iValue);
        }
        loopVars[0 + withIndex]->setIRValue(gep);
    } else {
        if (withIndex) {
            loopVars[0]->setIRValue(iValue);
        }
        const auto element = arr->getFunc->callIR(codeGen, {iterPtr, iValue});
        loopVars[0 + withIndex]->setIRValue(element);
    }
}

void LgsForeachLoop::setMapIterVars(LgsCodeGen& codeGen, const LgsIterator& iterator) const {
    const auto next = iterator.next(&codeGen);
    const auto entryType = codeGen.getStructType({codeGen.ptrTy(), codeGen.ptrTy()}, "MapEntry");
    const auto keyGEP = codeGen.builder.CreateStructGEP(entryType, next, 0);
    const auto valueGEP = codeGen.builder.CreateStructGEP(entryType, next, 1);
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
}
