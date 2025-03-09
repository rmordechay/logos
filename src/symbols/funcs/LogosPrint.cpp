#include "funcs/LogosPrint.h"

Value* LogosPrint::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

Value* LogosPrint::call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    const auto argType = args[0]->type->getIRType();
    auto argValue = args[0]->writeIRValue(metadata);
    FunctionCallee func;
    if (argType == metadata->builder.getPtrTy()) {
        func = metadata->currentModule->getOrInsertFunction(IRNameString, funcTypeString);
    } else {
        func = metadata->currentModule->getOrInsertFunction(IRNameInt, funcTypeInt);
    }
    return metadata->builder.CreateCall(func, {argValue});
}
