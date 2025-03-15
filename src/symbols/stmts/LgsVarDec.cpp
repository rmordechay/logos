#include "stmts/LgsVarDec.h"
#include "constants/LgsConst.h"
#include <LgsStack.h>

Value* LgsVarDec::createIRValue(CodeGenMetadata* metadata) {
    Value* exprValue;
    if (expr) {
        exprValue = expr->getIRValue(metadata);
    } else {
        exprValue = type->getZeroValue()->getIRValue(metadata);
    }
    const auto valueType = exprValue->getType();
    if (!valueType->isPointerTy()) {
        auto& builder = metadata->builder;
        const auto allocaInst = builder.CreateAlloca(valueType);
        builder.CreateStore(exprValue, allocaInst);
    }
    metadata->logosStack.addLocalSymbol(name, this);
    return exprValue;
}

LgsVarDec::~LgsVarDec() {
    delete expr;
}
