#include "funcs/LogosPrint.h"

#include <llvm/IR/Module.h>

Value* LogosPrint::computeIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}

Value* LogosPrint::callFunc(CodeGenMetadata* metadata, const vector<LogosExpr*>& args) {
    auto argValue = args[0]->writeIRValue(metadata);
    const auto valueName = argValue->getName();
    string funcName;
    if (valueName.find(".str") != std::string::npos) {
        funcName = IRNamePrint;
    } else {
        funcName = IRNameInt;
    }
    const auto func = metadata->currentModule->getOrInsertFunction(funcName, argValue->getType());
    return metadata->builder.CreateCall(func, {argValue});
}
