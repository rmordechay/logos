#include "funcs/LogosPrint.h"

Value* LogosPrint::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

Value* LogosPrint::call(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    const auto argType = args[0]->type->getIRType();
    auto argValue = args[0]->getIRValue(metadata);
    FunctionCallee func;
    if (argType == metadata->builder.getPtrTy()) {
        func = metadata->currentModule->getOrInsertFunction(IRNameString, funcTypeString);
    } else {
        func = metadata->currentModule->getOrInsertFunction(IRNameInt, funcTypeInt);
    }
    return metadata->builder.CreateCall(func, {argValue});
}
