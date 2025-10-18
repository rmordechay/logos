#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

std::string LgsNullableExpr::asText() {
    if (baseExpr) return baseExpr->asText();
    return nullLiteral;
}

void LgsNullableExpr::completeType(LgsType* toType) {
    const auto otherNullable = toType->asNullable();
    if (!otherNullable) return;
    if (isNull && !baseExpr) {
        type->asNullable()->baseType = otherNullable->baseType;
    }
}

void LgsNullableExpr::store(LgsLLVMGen& cg, Value* value, const bool isSet) const {
    const auto nullStruct = type->asNullable()->getIRType(cg);
    const auto isSetField = cg.builder.CreateStructGEP(nullStruct, IRValue, 1);
    cg.builder.CreateStore(isSet ? cg.true_() : cg.false_(), isSetField);
    if (isSet) {
        const auto vField = cg.builder.CreateStructGEP(nullStruct, IRValue, 0);
        cg.builder.CreateStore(value, vField);
    }
}

void LgsNullableExpr::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    if (isNull) store(cg, nullptr, false);
    else store(cg, expr->IRValue, true);
}

LgsNullableExpr::~LgsNullableExpr() {
    freeType(type);
    type = nullptr;
}
