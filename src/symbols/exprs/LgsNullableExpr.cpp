#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsLLVMGen.h"
#include "utils/LgsUtils.h"

std::string LgsNullableExpr::getName() {
    return "null";
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
    if (isSet) {
        cg.builder.CreateStore(cg.true_(), isSetField);
        const auto vField = cg.builder.CreateStructGEP(nullStruct, IRValue, 0);
        cg.builder.CreateStore(value, vField);
    }
}

LgsNullableExpr::~LgsNullableExpr() {
    freeType(type);
    type = nullptr;
}
