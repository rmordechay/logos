#include "LogosVarDefinition.h"

const LogosType& LogosVarDefinition::getType() const {
    return expr->type;
}

Value* LogosVarDefinition::getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) {
    const auto value = expr->getLLVMValue(builder, stackFrame, module);
    const auto allocaInst = builder->CreateAlloca(value->getType());
    builder->CreateStore(value, allocaInst);
    stackFrame->symbolTable[name] = allocaInst;
    return allocaInst;
}