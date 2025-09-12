#include "types/iterables/LgsDArray.h"
#include "exprs/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsDArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    return getArrStruct(cg);
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

StructType* LgsDArray::getArrStruct(LgsLLVMGen& cg) {
    if (arrStruct) return arrStruct;
    arrStruct = cg.getStructType({cg.i64Ty(), cg.ptrTy()}, name);
    return arrStruct;
}

void LgsDArray::freeValue(LgsLLVMGen& cg, Value* value) {
    cg.printPtr(value, "Freeing arr: ");
    freeFunc->callIR(cg, {value});
}

Value* LgsDArray::IRLength(LgsLLVMGen& cg, LgsExpr* iterable) {
    return lenFunc->callIR(cg, {iterable->IRValue});
}

Value* LgsDArray::IRIsEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return isEmptyFunc->call(*cg, {iterable});
}

Value* LgsDArray::IRIsNotEmpty(LgsLLVMGen* cg, LgsExpr* iterable) {
    return isNotEmptyFunc->call(*cg, {iterable});
}

bool LgsDArray::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
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
