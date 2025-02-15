#include "stmts/LogosVarDec.h"

Value* LogosVarDec::getLLVMValue(CodeGenMetadata* metadata) {
    if (llvmValue) return llvmValue;
    const auto value = expr->getLLVMValue(metadata);
    const auto valueType = value->getType();
    if (!valueType->isPointerTy()) {
        const auto allocaInst = metadata->builder->CreateAlloca(valueType);
        metadata->builder->CreateStore(value, allocaInst);
    }
    llvmValue = value;
    metadata->theStack->addLocalSymbol(name, expr->createSymbol());
    return value;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
