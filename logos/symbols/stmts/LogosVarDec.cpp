#include "LogosVarDec.h"

const LogosType& LogosVarDec::getType() const {
    return expr->type;
}

Value* LogosVarDec::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    const auto value = expr->getLLVMValue(builder, stackFrame, module);
    const auto allocaInst = builder->CreateAlloca(value->getType());
    builder->CreateStore(value, allocaInst);
    stackFrame->symbolTable[name] = allocaInst;
    return allocaInst;
}