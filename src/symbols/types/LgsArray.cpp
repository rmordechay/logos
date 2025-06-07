#include "types/LgsArray.h"
#include "utils/LgsUtils.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "logos/LgsConfig.h"
#include "logos/LgsRuntime.h"
#include "stmts/LgsVarDec.h"

size_t LgsArray::getSizeBytes() {
    if (isStatic) {
        return baseType->getSizeBytes() * LgsExpr::getExprConstNumber(sizeExpr);
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
