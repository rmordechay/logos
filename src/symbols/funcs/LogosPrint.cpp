#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

Value* LogosPrint::call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    const auto argType = args[0]->type->getIRType();
    auto argValue = args[0]->writeIRValue(metadata);
    string funcName;
    if (argType == metadata->builder.getPtrTy()) {
        funcName = IRNameString;
    } else {
        funcName = IRNameInt;
    }
    const auto func = metadata->currentModule->getOrInsertFunction(funcName, metadata->builder.getVoidTy());
    return metadata->builder.CreateCall(func, {argValue});
}
