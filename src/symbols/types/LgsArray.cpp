#include "types/LgsArray.h"
#include "utils/LgsUtils.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "logos/LgsConfig.h"

#include "stmts/LgsVarDec.h"

size_t LgsArray::getSizeBytes() {
    if (isStatic) {
        return baseType->getSizeBytes() * LgsExpr::getExprConstNumber(sizeExpr);
    }
    return sizeof(void*);
}

LgsExpr* LgsArray::getZeroValue() {
    const auto arrExpr = new LgsArrayExpr(baseType->clone());
    arrExpr->arrType.isStatic = isStatic;
    arrExpr->arrType.sizeExpr = sizeExpr;
    return arrExpr;
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
    if (!exprs.empty()) {
        baseType = exprs.front()->type;
    }
    sizeExpr = new LgsIntConst(exprs.size());
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}

void LgsArray::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}

Value* LgsArray::getLength(LgsRuntime* runtime, LgsExpr* expr) {
    if (isStatic) return sizeExpr->getIRValue(runtime);
    return len.call(runtime, {expr});
}

Value* LgsArray::getLoopLength(LgsRuntime* runtime, LgsExpr* expr) {
    return getLength(runtime, expr);
}

Value* LgsArray::callIsEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isEmpty.call(runtime, {expr});
}

Value* LgsArray::callIsNotEmpty(LgsRuntime* runtime, LgsExpr* expr) {
    return isNotEmpty.call(runtime, {expr});
}

LgsType* LgsArray::clone() {
    const auto arr = new LgsArray(baseType);
    if (sizeExpr) {
        arr->isStatic = isStatic;
        arr->sizeExpr = sizeExpr;
    }
    return arr;
}

LgsArray::~LgsArray() {
    delete sizeExpr;
}
