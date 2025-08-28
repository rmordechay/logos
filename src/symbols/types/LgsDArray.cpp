#include "types/LgsDArray.h"
#include "builtins/LgsPrint.h"
#include "exprs/unary/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsDArray::getIRType(LgsLLVM& codeGen) {
    if (IRType) return IRType;
    return getArrStruct(codeGen);
}

std::string LgsDArray::getName() {
    return name;
}

std::string LgsDArray::pname() {
    assert(baseType);
    return baseType->pname() + "[]";
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

uint16_t LgsDArray::getUnpackCount() const {
    return 1;
}

std::string LgsDArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

StructType* LgsDArray::getArrStruct(LgsLLVM& codeGen) {
    if (arrStruct) return arrStruct;
    arrStruct = codeGen.getStructType({codeGen.i64Ty(), codeGen.i64Ty(), codeGen.i64Ty(), codeGen.ptrTy()}, name);
    return arrStruct;
}

void LgsDArray::freeValue(LgsLLVM& codeGen, Value* value) {
    freeFunc->callIR(codeGen, {value});
}

Value* LgsDArray::IRLength(LgsLLVM& codeGen, LgsExpr* iterable) {
    return lenFunc->call(codeGen, {iterable});
}

Value* LgsDArray::IRIsEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return isEmptyFunc->call(*codeGen, {iterable});
}

Value* LgsDArray::IRIsNotEmpty(LgsLLVM* codeGen, LgsExpr* iterable) {
    return isNotEmptyFunc->call(*codeGen, {iterable});
}

bool LgsDArray::canCastTo(LgsType* other) {
    const auto otherArr = other->asDArray();
    if (!otherArr) return false;
    if (!baseType) return true;
    return baseType->canCastTo(otherArr->baseType);
}

json::value LgsDArray::asJSON() {
    json::object jsonObj;
    jsonObj["name"] = name;
    return jsonObj;
}
