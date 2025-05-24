#include "types/array/LgsArray.h"
#include "LgsUtils.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "stmts/LgsVarDec.h"

void LgsArray::inferArrayType(const vector<LgsExpr*>& exprs) {
    baseType = inferTypeFromIter(exprs);
    dimsExprs = {new LgsIntConst(exprs.size())};
}

LgsExpr* LgsArray::getZeroValue() {
    const auto arr = new LgsArrayExpr(baseType);
    for (const auto dimsExpr : dimsExprs) {
        arr->arrType.dimsExprs.emplace_back(dimsExpr->clone());
    }
    arr->arrType.isStatic = isStatic;
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

int LgsArray::getDims() {
    return dimsExprs.size();
}

string LgsArray::getIRName() {
    return name;
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}

bool LgsArray::canIndexTo(LgsType* indexType) {
    return !!indexType->asInt();
}

void LgsArray::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}

Value* LgsArray::getLength(CodeGenMetadata* metadata, Value* iter) {
    if (isStatic) return dimsExprs[0]->getIRValue(metadata);
    return len.callIR(metadata, {iter});
}

Value* LgsArray::getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* iPtr) {
    if (isStatic) {
        const auto i = metadata->builder.CreateLoad(i32Ty, iPtr);
        return metadata->builder.CreateGEP(getIRType(), iterPtr, {i32Zero, i});
    }
    const auto iValue = metadata->builder.CreateLoad(i32Ty, iPtr);
    const auto v = get.callIR(metadata, {iterPtr, iValue});
    return metadata->builder.CreateLoad(getIRType(), v);
}

LgsType* LgsArray::createInnerType(const size_t indexRange, LgsIndex* index) const {
    if (!isStatic) assert(false);
    const auto innerType = new LgsArray(baseType);
    innerType->isStatic = isStatic;
    innerType->dimsExprs = dimsExprs;
    if (index->to) {
        const auto from = getExprConstNumber(index->from);
        const auto to = getExprConstNumber(index->to);
    } else {
        const auto i = innerType->dimsExprs.size() - 1 - indexRange;
        innerType->dimsExprs.erase(innerType->dimsExprs.begin() + i);
    }
    return innerType;
}

LgsArray::~LgsArray() {
    for (const auto dimsExpr : dimsExprs) {
        delete dimsExpr;
    }
}
