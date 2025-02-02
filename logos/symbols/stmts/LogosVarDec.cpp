#include "LogosVarDec.h"

#include "AntlrConverter.h"
#include "../LogosStack.h"

#include <llvm/IR/Module.h>

Value* LogosVarDec::getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) {
    const auto value = expr->getLLVMValue(builder, theStack, module);
    const auto allocaInst = builder->CreateAlloca(value->getType(), nullptr);
    builder->CreateStore(value, allocaInst);
    theStack->addSymbol(name, LogosSymbol(VAR_DEC, this));
    return allocaInst;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
