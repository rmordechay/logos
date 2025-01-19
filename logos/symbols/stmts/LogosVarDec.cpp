#include "LogosVarDec.h"
#include "LogosStack.h"

Value* LogosVarDec::getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) {
    const auto value = expr->getLLVMValue(builder, stackFrame, module);
    const auto allocaInst = builder->CreateAlloca(value->getType(), nullptr, name);
    builder->CreateStore(value, allocaInst);
    stackFrame->addSymbol(name, allocaInst);
    return allocaInst;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
