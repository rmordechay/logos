#include "types/LgsNullable.h"
#include "codegen/LgsLLVMGen.h"
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
    const auto nullableExpr = new LgsNullableExpr();
    nullableExpr->type = this;
    return nullableExpr;
}

Lgs_RTType LgsNullable::getRTType() {
    assert(0);
}

std::string LgsNullable::getName() {
    return baseType->getName() + "?";
}

std::string LgsNullable::pname() {
    return baseType->pname() + '?';
}

json::value LgsNullable::asJsonStr() {
    assert(0);
}

bool LgsNullable::canCastTo(LgsType* other) {
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

LgsNullable::~LgsNullable() {
    if (baseType) {
        freeType(baseType);
        baseType = nullptr;
    }
}
