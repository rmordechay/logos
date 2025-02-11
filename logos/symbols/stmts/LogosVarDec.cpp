#include "LogosVarDec.h"

#include "AntlrConverter.h"
#include "../LogosStack.h"

#include <llvm/IR/Module.h>

Value* LogosVarDec::getLLVMValue(CodeGenMetadata* metadata) {
    const auto value = expr->getLLVMValue(metadata);
    const auto allocaInst = metadata->builder->CreateAlloca(value->getType(), nullptr);
    metadata->builder->CreateStore(value, allocaInst);
    metadata->theStack->addSymbol(name, LogosSymbol(VAR_DEC, this));
    return allocaInst;
}

LogosVarDec::~LogosVarDec() {
    delete expr;
}
