#include "types/LgsDArray.h"
#include "builtins/LgsBuiltins.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsDArray::getIRType(LgsCodeGen* codeGen) {
    if (IRType) return IRType;
    return getArrStruct(codeGen);
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

std::string LgsDArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

std::string LgsDArray::getName() {
    return name;
}

json::value_ref LgsDArray::asJSON() {
    json::object obj;
    return obj;
}

std::string LgsDArray::pname() {
    assert(baseType);
    return baseType->pname() + "[]";
}

uint16_t LgsDArray::getUnpackCount() const {
    return 1;
}

bool LgsDArray::equals(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    return baseType->equals(otherArr->baseType);
}

void LgsDArray::freeValue(LgsCodeGen* codeGen, Value* value) {
    freeFunc->callIR(codeGen, {value});
}

Value* LgsDArray::IRLength(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return lenFunc->call(codeGen, {iterable});
}

Value* LgsDArray::IRIsEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isEmptyFunc->call(codeGen, {iterable});
}

Value* LgsDArray::IRIsNotEmpty(LgsCodeGen* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc->call(codeGen, {iterable});
}

StructType* LgsDArray::getArrStruct(LgsCodeGen* codeGen) {
    if (arrStruct) return arrStruct;
    arrStruct = codeGen->getStructType({codeGen->i64Ty(), codeGen->i64Ty(), codeGen->i64Ty(), codeGen->ptrTy()}, name);
    return arrStruct;
}

Value* LgsArrayAddFunc::call(LgsCodeGen* codeGen, const std::vector<LgsExpr*>& args) {
    const auto arr = args[0];
    const auto exprToAdd = args[1];
    const auto exprIR = exprToAdd->getIRValue(codeGen);
    const auto arrPtr = arr->getIRValue(codeGen);
    const auto exprTy = exprToAdd->type;
    const auto ptr = codeGen->builder.CreateAlloca(exprTy->getIRType(codeGen));
    codeGen->builder.CreateStore(exprIR, ptr);
    return callIR(codeGen, {arrPtr, ptr});
}

LgsDArray::~LgsDArray() {
    delete sizeExpr;
}
