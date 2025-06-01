#include "types/array/LgsArray.h"
#include "utils/LgsUtils.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "logos/LgsConfig.h"
#include "stmts/LgsVarDec.h"

size_t LgsArray::getSize() {
    if (isStatic) {
        return baseType->getSize() * getExprConstNumber(sizeExpr);
    }
    return sizeof(void*);
}

LgsExpr* LgsArray::getZeroValue() {
    const auto arr = new LgsArrayExpr(baseType->clone());
    if (sizeExpr) {
        arr->arrType.isStatic = sizeExpr->type->isConst;
        arr->arrType.sizeExpr = sizeExpr->clone();
    } else {
        arr->arrType.sizeExpr = new LgsIntConst(INITIAL_ARRAY_CAPACITY);
    }
    return arr;
}

string LgsArray::prettyName() const {
    return name;
}

bool LgsArray::equals(LgsType* other) {
    const auto otherArr = other->asArray();
    if (!otherArr) return false;
    return baseType->equals(otherArr->baseType);
}

string LgsArray::getIRName() {
    return name;
}

void LgsArray::inferArrayType(const vector<LgsExpr*>& exprs) {
    baseType = exprs.front()->type;
    sizeExpr = new LgsIntConst(exprs.size());
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}

void LgsArray::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}

Value* LgsArray::getLength(Module* module, Value* iterValue) {
    if (isStatic) return sizeExpr->getIRValue(module);
    return len.callIR(module, {iterValue});
}

Value* LgsArray::getElement(Module* module, Value* iterPtr, Value* indexPtr) {
    if (isStatic) {
        const auto i = builder.CreateLoad(i32Ty, indexPtr);
        return builder.CreateGEP(getIRType(), iterPtr, {i32Zero, i});
    }
    const auto iValue = builder.CreateLoad(i32Ty, indexPtr);
    const auto v = get.callIR(module, {iterPtr, iValue});
    return builder.CreateLoad(getIRType(), v);
}

LgsType* LgsArray::clone() {
    const auto lgsArray = new LgsArray(baseType);
    if (sizeExpr) {
        lgsArray->isStatic = sizeExpr->type->isConst;
        lgsArray->sizeExpr = sizeExpr;
    }
    return lgsArray;
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
