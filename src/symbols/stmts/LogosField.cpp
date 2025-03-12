#include "stmts/LogosField.h"

#include "LogosInstance.h"
#include "exprs/LogosExpr.h"
#include "types/LogosObject.h"

Value* LogosField::createIRValue(CodeGenMetadata* metadata) {
    if (!gep) {
        const auto parentTy = StructType::getTypeByName(context, parentName);
        const auto self = metadata->logosStack.currentFunc->getArg(0);
        gep = metadata->builder.CreateStructGEP(parentTy, self, fieldPosition);
    }
    const auto ty = type->getIRType();
    return metadata->builder.CreateLoad(ty, gep);
}

void LogosField::setFieldIRValue(CodeGenMetadata* metadata, LogosExpr* lvalueExpr, LogosInstance* instance) {
    const auto ty = instance->obj->getIRType();
    const auto v = instance->getIRValue(metadata);
    gep = metadata->builder.CreateStructGEP(ty, v, fieldPosition);
    const auto exprIRValue = lvalueExpr->getIRValue(metadata);
    metadata->builder.CreateStore(exprIRValue, gep);
}