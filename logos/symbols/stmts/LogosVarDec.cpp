#include "LogosVarDec.h"

Value* LogosVarDec::getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) {
    const auto value = expr->getLLVMValue(builder, stackFrame, module);
    const auto allocaInst = builder->CreateAlloca(value->getType());
    builder->CreateStore(value, allocaInst);
    stackFrame->top().symbolTable[name] = allocaInst;
    return allocaInst;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
