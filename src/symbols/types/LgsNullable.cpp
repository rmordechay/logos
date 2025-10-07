#include "types/LgsNullable.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "exprs/LgsNullableExpr.h"
#include "utils/LgsUtils.h"

LgsField* LgsNullable::getField(const std::string& fieldName) {
    return baseType->getField(fieldName);
}

LgsFunc* LgsNullable::getMethod(const std::string& methodName) {
    return baseType->getMethod(methodName);
}

Type* LgsNullable::getIRType(LgsLLVMGen& cg) {
    return cg.getStructType({baseType->getIRType(cg), cg.i1Ty()});
}

LgsExpr* LgsNullable::getZeroValue() {
    const auto nullableExpr = new LgsNullableExpr(nullptr);
    nullableExpr->type = this;
    return nullableExpr;
}

Lgs_rttype LgsNullable::getRTType() {
    return RTT_NULLABLE;
}

std::string LgsNullable::getName() {
    return baseType->getName() + "?";
}

std::string LgsNullable::pname() {
    return baseType ? baseType->pname() + '?' : LGS_UNKNOWN_TYPE;
}

bool LgsNullable::canCastTo(LgsType* other) {
    if (other->getName() == LgsAny::name) return true;
    const auto otherNullable = other->asNullable();
    if (!otherNullable) return false;
    return baseType->canCastTo(otherNullable->baseType);
}

size_t LgsNullable::getSizeBytes() {
    return baseType->getSizeBytes() + sizeof(bool);
}

std::string LgsNullable::strFormatPart() const {
    return baseType->strFormatPart();
}

Value* LgsNullable::isNullIR(LgsLLVMGen& cg, Value* ptr) {
    auto nullableField = cg.builder.CreateStructGEP(getIRType(cg), ptr, 1);
    nullableField = cg.builder.CreateLoad(cg.i1Ty(), nullableField);
    return cg.builder.CreateICmpEQ(cg.true_(), nullableField);
}

Value* LgsNullable::getValue(LgsLLVMGen& cg, Value* ptr) {
    const auto gep = cg.builder.CreateStructGEP(getIRType(cg), ptr, 0);
    if (baseType->asObject()) {
        return cg.builder.CreateLoad(cg.ptrTy(), gep);
    }
    return gep;
}

LgsNullable::~LgsNullable() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
