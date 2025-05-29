#include "types/array/LgsArray.h"
#include "utils/LgsUtils.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "exprs/unary/LgsIterIndex.h"
#include "exprs/unary/constants/LgsIntConst.h"
#include "logos/LgsConfig.h"
#include "stmts/LgsVarDec.h"

size_t LgsArray::getSize() {
    if (isStatic) {
        return baseType->getSize() * getExprConstNumber(dimsExpr);
    }
    return sizeof(void*);
}

LgsExpr* LgsArray::getZeroValue() {
    const auto arr = new LgsArrayExpr(baseType->clone());
    if (dimsExpr) {
        arr->arrType.isStatic = dimsExpr->type->isConst;
        arr->arrType.dimsExpr = dimsExpr->clone();
    } else {
        arr->arrType.dimsExpr = new LgsIntConst(INITIAL_ARRAY_CAPACITY);
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

StructType* LgsArray::getIRStructType() const {
    const auto arrStruct = StructType::getTypeByName(context, name);
    if (!arrStruct) {
        return StructType::create(context, {i64Ty, i32Ty, i32Ty, ptrTy}, name);
    }
    return arrStruct;
}

void LgsArray::inferArrayType(const vector<LgsExpr*>& exprs) {
    baseType = exprs.front()->type;
    dimsExpr = new LgsIntConst(exprs.size());
}

LgsType* LgsArray::inferBinaryType(LgsType* other) {
    assert(false);
}

void LgsArray::unpackTypes(const vector<LgsVarDec*>& varDecs) {
    varDecs[0]->type = baseType;
}

Value* LgsArray::getLength(CodeGenMetadata* metadata, Value* iterValue) {
    if (isStatic) return dimsExpr->getIRValue(metadata);
    return len.callIR(metadata, {iterValue});
}

Value* LgsArray::getElement(CodeGenMetadata* metadata, Value* iterPtr, Value* indexPtr) {
    if (isStatic) {
        const auto i = metadata->builder.CreateLoad(i32Ty, indexPtr);
        return metadata->builder.CreateGEP(getIRType(), iterPtr, {i32Zero, i});
    }
    const auto iValue = metadata->builder.CreateLoad(i32Ty, indexPtr);
    const auto v = get.callIR(metadata, {iterPtr, iValue});
    return metadata->builder.CreateLoad(getIRType(), v);
}

LgsType* LgsArray::clone() {
    const auto lgsArray = new LgsArray(baseType);
    if (dimsExpr) {
        lgsArray->isStatic = dimsExpr->type->isConst;
        lgsArray->dimsExpr = dimsExpr;
    }
    return lgsArray;
}

LgsArray::~LgsArray() {
    delete dimsExpr;
}
