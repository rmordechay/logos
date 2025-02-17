#include "stmts/LogosVarDec.h"

#include "LogosUtils.h"

Value* LogosVarDec::computeLLVMValue(CodeGenMetadata* metadata) {
    const auto value = expr->getLLVMValue(metadata);
    const auto valueType = value->getType();
    if (!valueType->isPointerTy()) {
        const auto allocaInst = metadata->builder->CreateAlloca(valueType);
        metadata->builder->CreateStore(value, allocaInst);
    }
    const auto symbol = Utils::createSymbol(expr);
    metadata->theStack->addLocalSymbol(name, symbol);
    return value;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
