#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsLLVMGen.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/Module.h>

std::string LgsNullableExpr::asText() {
    if (baseExpr) return baseExpr->asText();
    return LGS_NULL_LITERAL;
}

void LgsNullableExpr::completeType(LgsType* toType) {
    const auto otherNullable = toType->asNullable();
    if (!otherNullable) return;
    if (isNull && !baseExpr) {
        type->asNullable()->baseType = otherNullable->baseType;
    }
}

void LgsNullableExpr::assign(LgsLLVMGen& cg, LgsExpr* expr) {
    const auto nullStruct = type->getIRType(cg);
    const auto valueField = cg.builder.CreateStructGEP(nullStruct, IRValue, 0);
    const auto isSetField = cg.builder.CreateStructGEP(type->getIRType(cg), IRValue, 1);
    if (expr->asNullableExpr()->isNull) {
        cg.builder.CreateStore(cg.false_(), isSetField);
    } else {
        cg.builder.CreateStore(cg.true_(), isSetField);
        cg.builder.CreateStore(expr->IRValue, valueField);
    }
}

LgsNullableExpr::~LgsNullableExpr() {
    freeType(type);
    type = nullptr;
}
