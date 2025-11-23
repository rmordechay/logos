#include "types/LgsNullable.h"
#include "codegen/LgsLLVMGen.h"
#include "LgsDefinitions.h"
#include "exprs/LgsNull.h"
#include "LgsUtils.h"
#include "types/LgsAny.h"

LgsField* LgsNullable::getField(const std::string& fieldName) {
    return baseType->getField(fieldName);
}

LgsFunc* LgsNullable::getMethod(const std::string& methodName) {
    return baseType->getMethod(methodName);
}

void LgsNullable::setIRValue(LgsLLVMGen& cg, Value* nullablePtr, Value* value) {
    if (baseType->passByRef) {
        cg.builder.CreateStore(value, nullablePtr);
    } else {
        const auto ty = getIRType(cg);
        const auto valueField = cg.builder.CreateStructGEP(ty, nullablePtr, 0);
        const auto isSetField = cg.builder.CreateStructGEP(ty, nullablePtr, 1);
        cg.builder.CreateStore(cg.builder.CreateIsNotNull(value), isSetField);
        cg.builder.CreateStore(value, valueField);
    }
}

Type* LgsNullable::getIRType(LgsLLVMGen& cg) {
    return cg.getStructType({baseType->getIRType(cg), cg.i1Ty()}, "nullable_" + baseType->getName());
}

Constant* LgsNullable::getRTType(LgsLLVMGen& cg) {
    const auto genericName = getGenericName();
    const auto st = cg.getStructType({cg.ptrTy()}, genericName);
    const auto sv = llvm::ConstantStruct::get(st, {baseType->getRTType(cg)});
    return cg.getRTTypeInfo(genericName, sizeBytes(), RTT_NULLABLE, sv);
}

LgsExpr* LgsNullable::getZeroValue() {
    return new LgsNull();
}

std::string LgsNullable::getName() {
    return baseType ? baseType->getName() + '?' : "Null";
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

size_t LgsNullable::sizeBytes() {
    return baseType->sizeBytes() + sizeof(bool);
}

std::string LgsNullable::strFormatPart() const {
    return baseType->strFormatPart();
}

llvm::DIType* LgsNullable::getDebugType(LgsLLVMGen& cg) {
    assert(0);
}

LgsType* LgsNullable::clone() {
    const auto newNullable = new LgsNullable(*this);
    newNullable->baseType = baseType->clone();
    return newNullable;
}

LgsNullable::~LgsNullable() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
