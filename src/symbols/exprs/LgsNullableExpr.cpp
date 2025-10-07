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

void LgsNullableExpr::storeValue(LgsLLVMGen& cg, Value* value, const bool null) const {
    const auto nullStruct = type->asNullable()->getIRType(cg);
    const auto isNullField = cg.builder.CreateStructGEP(nullStruct, IRValue, 1);
    if (null) {
        cg.builder.CreateStore(cg.true_(), isNullField);
        return;
    }
    cg.builder.CreateStore(cg.false_(), isNullField);
    assert(value);
    const auto vField = cg.builder.CreateStructGEP(nullStruct, IRValue, 0);
    cg.builder.CreateStore(value, vField);
}

LgsNullableExpr::~LgsNullableExpr() {
    freeType(type);
    type = nullptr;
}
