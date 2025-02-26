#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

Value* LogosPrint::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    const auto func = metadata->currentModule->getOrInsertFunction(IRName, funcTypeInt);
    const auto arg = {args[0]->writeIRValue(metadata)};
    return metadata->builder.CreateCall(func, arg);
}
