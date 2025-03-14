#include "stmts/LgsVarDec.h"
#include "constants/LgsConstant.h"
#include <LgsStack.h>

Value* LgsVarDec::createIRValue(CodeGenMetadata* metadata) {
    Value* value;
    if (expr) {
        value = expr->getIRValue(metadata);
    } else {
        value = type->getZeroValue()->getIRValue(metadata);
    }
    const auto valueType = value->getType();
    if (!valueType->isPointerTy()) {
        auto& builder = metadata->builder;
        const auto allocaInst = builder.CreateAlloca(valueType);
        builder.CreateStore(value, allocaInst);
    }
    metadata->logosStack.addLocalSymbol(name, LgsSymbol(VAR_DEC, this));
    return value;
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}
