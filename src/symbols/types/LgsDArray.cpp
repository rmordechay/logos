#include "types/LgsDArray.h"
#include "builtin/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"
#include "utils/LgsUtils.h"

Type* LgsDArray::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    return getArrStruct();
}

size_t LgsDArray::getSizeBytes() {
    return sizeof(size_t) + sizeof(size_t) + sizeof(size_t) + sizeof(void*);
}

LgsExpr* LgsDArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

LgsType* LgsDArray::getIndexType() {
    return &LGS_INT;
}

LgsType* LgsDArray::getValueType() {
    return baseType;
}

string LgsDArray::getStrFormatPart() const {
    return "%p";
}

string LgsDArray::prettyName() {
    return baseType->prettyName() + "[]";
}

bool LgsDArray::equals(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    return baseType->equals(otherArr->baseType);
}

string LgsDArray::getName() {
    return name;
}

Value* LgsDArray::getLength(LgsExpr* expr) {
    return lenFunc.call(codeGen, {expr});
}

Value* LgsDArray::getLoopLength(LgsExpr* expr) {
    return getLength(expr);
}

Value* LgsDArray::isEmpty(LgsExpr* expr) {
    return isEmptyFunc.call(codeGen, {expr});
}

Value* LgsDArray::isNotEmpty(LgsExpr* expr) {
    return isNotEmptyFunc.call(codeGen, {expr});
}

StructType* LgsDArray::getArrStruct() {
    auto& context = codeGen->context;
    if (arrStruct) return arrStruct;
    arrStruct = codeGen->getIRStructType(name, {codeGen->i64Ty(), codeGen->i64Ty(), codeGen->i64Ty(), codeGen->ptrTy()});
    return arrStruct;
}

Value* LgsArrayAddFunc::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    const auto arr = args.front();
    const auto baseType = arr->type->asIterable()->baseType;
    const auto baseTypeIR = baseType->getIRType(codeGen);
    const auto valuePtr = codeGen->builder.CreateAlloca(baseTypeIR);
    codeGen->builder.CreateStore(args[1]->getIRValue(codeGen), valuePtr);
    return callIR(codeGen, {arr->getIRValue(codeGen), valuePtr});
}

LgsDArray::~LgsDArray() {
    delete sizeExpr;
}
