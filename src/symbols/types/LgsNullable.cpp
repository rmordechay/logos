#include "types/LgsNullable.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsNull.h"
#include "utils/LgsUtils.h"

LgsField* LgsNullable::getField(const std::string& fieldName) {
    return baseType->getField(fieldName);
}

LgsFunc* LgsNullable::getMethod(const std::string& methodName) {
    return baseType->getMethod(methodName);
}

Type* LgsNullable::getIRType(LgsLLVMGen& cg) {
    const auto type = baseType->isPrimitive ? baseType->getIRType(cg) : cg.ptrTy();
    return cg.getStructType({type, cg.i1Ty()}, "nullable_" + baseType->getName());
}

LgsExpr* LgsNullable::getZeroValue() {
    return new LgsNull();
}

Lgs_TypeKind LgsNullable::getRTTypeKind() {
    return RTT_NULLABLE;
}

std::string LgsNullable::getName() {
    return baseType ? baseType->getName() : "Null";
}

std::string LgsNullable::pname() {
    return (baseType ? baseType->pname() : LGS_UNKNOWN_TYPE) + '?';
}

bool LgsNullable::canCastTo(LgsType* other) {
    if (baseType->isVoid() && !other->isVoid()) return false;
    if (other->getName() == LgsAny::name) return true;
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    if (!baseType) return true;
    return baseType->canCastTo(otherNullable->baseType);
}

size_t LgsNullable::getSizeBytes() {
    return baseType->getSizeBytes() + sizeof(bool);
}

std::string LgsNullable::strFormatPart() const {
    return baseType->strFormatPart();
}

LgsNullable::~LgsNullable() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
