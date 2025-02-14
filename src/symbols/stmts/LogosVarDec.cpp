#include "stmts/LogosVarDec.h"

Value* LogosVarDec::writeLLVMValue(CodeGenMetadata* metadata) {
    const auto value = expr->writeLLVMValue(metadata);
    const auto valueType = value->getType();
    if (!valueType->isPointerTy()) {
        const auto allocaInst = metadata->builder->CreateAlloca(valueType);
        metadata->builder->CreateStore(value, allocaInst);
    }
    metadata->theStack->addLocalSymbol(name, LogosSymbol(VAR_DEC, this));
    llvmValue = value;
    return value;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
