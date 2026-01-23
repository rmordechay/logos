#include "types/LgsEnumField.h"
#include "codegen/LgsCgModule.h"
#include "types/LgsAny.h"
#include "types/LgsEnum.h"

std::string LgsEnumField::getName() {
    return name;
}

size_t LgsEnumField::sizeBytes() {
    assert(0);
}

LgsExpr* LgsEnumField::getZeroValue() {
    assert(0);
}

Type* LgsEnumField::getIRType(LgsCgModule& cg) {
    const auto subtype = parentType->subtype;
    const auto parentName = parentType->getName();
    if (subtype) return cg.getStructType({cg.sizeTy(), subtype->getIRType(cg)}, parentName);
    return cg.getStructType({cg.sizeTy(), cg.ptrTy()}, parentName);
}

Constant* LgsEnumField::getRTType(LgsCgModule& cg) {
    return cg.getRTTypeInfo(parentType->getName(), IRSize(cg), rtt);
}

bool LgsEnumField::canCastTo(LgsType* other) {
    const auto otherName = other->getName();
    if (otherName == LgsAny::name) return true;
    return parentType->getName() == otherName;
}

std::string LgsEnumField::fmtStr() const {
    return "%s";
}

Value* LgsEnumField::asIRStr(LgsCgModule& cg, Value* v) {
    return cg.getString(name);
}

LgsType* LgsEnumField::applyBinOp(LgsType* rightType, LgsBinOp& op) {
    assert(0);
}

DIType* LgsEnumField::getDebugType(LgsCgModule& cg) {
    assert(0);
}
