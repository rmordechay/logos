#include "types/iterables/LgsSArray.h"
#include "exprs/LgsArrayExpr.h"
#include "types/primitives/LgsInt.h"

Type* LgsSArray::getIRType(LgsLLVMGen& cg) {
    if (IRType) return IRType;
    const auto innerIRType = baseType->getIRType(cg);
    IRType = ArrayType::get(innerIRType, sizeExpr->getConstInt());
    return IRType;
}

std::string LgsSArray::getName() {
    return name;
}

std::string LgsSArray::pname() {
    const auto index = sizeExpr->getConstInt() == 0 ? "" : std::to_string(sizeExpr->getConstInt());
    const auto ty = baseType ? baseType->pname() : "";
    return ty + '[' + index + "]!";
}

size_t LgsSArray::getSizeBytes() {
    return baseType->getSizeBytes() * sizeExpr->getConstInt();
}

LgsExpr* LgsSArray::getZeroValue() {
    return new LgsArrayExpr(this);
}

Lgs_RTType LgsSArray::getRTType() {
    return RTT_SARRAY;
}

LgsType* LgsSArray::getIndexType() {
    return &LGS_INT;
}

uint16_t LgsSArray::getUnpackCount() const {
    return 1;
}

std::string LgsSArray::strFormatPart() const {
    if (baseType->asChar()) return "%s";
    return "%p";
}

Value* LgsSArray::IRLength(LgsLLVMGen& cg, Value* iterable) {
    return sizeExpr->IRValue;
}

bool LgsSArray::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherArr = other->asIterable();
    if (!otherArr) return false;
    return baseType->canCastTo(otherArr->baseType);
}

json::value LgsSArray::asJSON() {
    assert(0);
}

