#include "types/LgsDArray.h"
#include "builtin/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"
#include "utils/LgsUtils.h"

Type* LgsDArray::getIRType(LgsModule* module) {
    if (IRType) return IRType;
    return getArrStruct(module);
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

string LgsDArray::prettyName() const {
    return baseType->prettyName() + "[]";
}

bool LgsDArray::equals(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    return baseType->equals(otherArr->baseType);
}

string LgsDArray::getIRName() {
    return name;
}

Value* LgsDArray::getLength(LgsModule* module, LgsExpr* expr) {
    return lenFunc.call(module, {expr});
}

Value* LgsDArray::getLoopLength(LgsModule* module, LgsExpr* expr) {
    return getLength(module, expr);
}

Value* LgsDArray::isEmpty(LgsModule* module, LgsExpr* expr) {
    return isEmptyFunc.call(module, {expr});
}

Value* LgsDArray::isNotEmpty(LgsModule* module, LgsExpr* expr) {
    return isNotEmptyFunc.call(module, {expr});
}

StructType* LgsDArray::getArrStruct(LgsModule* module) {
    auto& context = module->context;
    if (arrStruct) return arrStruct;
    arrStruct = getIRStructType(context, name, {i64Ty(module), i64Ty(module), i64Ty(module), ptrTy(module)});
    return arrStruct;
}

Value* LgsArrayAddFunc::call(LgsModule* module, const vector<LgsExpr*>& args) {
    vector<Value*> values;
    const auto arr = args[0];
    const auto arrPtr = arr->getIRValue(module);
    const auto value = args[1]->getIRValue(module);
    const auto baseType = arr->type->asIterable()->baseType;
    const auto baseTypeIR = baseType->getIRType(module);
    const auto valuePtr = module->builder.CreateAlloca(baseTypeIR);
    module->builder.CreateStore(value, valuePtr);
    callIR(module, {arrPtr, valuePtr});
    return nullptr;
}

LgsDArray::~LgsDArray() {
    delete sizeExpr;
}
