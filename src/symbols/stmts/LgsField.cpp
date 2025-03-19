#include "stmts/LgsField.h"

#include "exprs/unary/LgsInstance.h"
#include "exprs/LgsExpr.h"
#include "types/LgsObject.h"

Value* LgsField::getIRValue(CodeGenMetadata* metadata) {
    if (IRValue) return IRValue;
    return createIRValue(metadata);
}

Value* LgsField::createIRValue(CodeGenMetadata* metadata) {
    if (!gep) {
        const auto parentTy = StructType::getTypeByName(context, parentName);
        const auto self = metadata->logosStack.currentFunc->getArg(0);
        gep = metadata->builder.CreateStructGEP(parentTy, self, fieldPosition);
    }
    const auto ty = type->getIRType();
    return metadata->builder.CreateLoad(ty, gep);
}

void LgsField::setFieldIRValue(CodeGenMetadata* metadata, LgsExpr* lvalueExpr, LgsInstance* instance) {
    const auto ty = instance->obj->getIRType();
    const auto v = instance->getIRValue(metadata);
    gep = metadata->builder.CreateStructGEP(ty, v, fieldPosition);
    const auto exprIRValue = lvalueExpr->getIRValue(metadata);
    metadata->builder.CreateStore(exprIRValue, gep);
}