#include "stmts/LogosVarDec.h"

Value* LogosVarDec::getLLVMValue(CodeGenMetadata* metadata) {
    const auto value = expr->getLLVMValue(metadata);
    const auto allocaInst = metadata->builder->CreateAlloca(value->getType());
    metadata->builder->CreateStore(value, allocaInst);
    metadata->theStack->addLocalSymbol(name, LogosSymbol(VAR_DEC, this));
    return allocaInst;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
