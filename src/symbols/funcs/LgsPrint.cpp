#include "funcs/LgsPrint.h"
#include "CodeGenMetadata.h"

Value* LgsPrint::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    if (!IRFunc) setIRFunc(metadata);
    auto argValue = args[0]->getIRValue(metadata);
    return metadata->builder.CreateCall(IRFunc, {argValue});
}

void LgsPrint::setIRFunc(CodeGenMetadata* metadata) {
    vector<Type*> paramTypes;
    for (const auto& param : params) {
        paramTypes.emplace_back(param->type->getIRType());
    }
    const auto IRFuncType = FunctionType::get(LOGOS_VOID.IRType, paramTypes, false);
    IRFunc = Function::Create(IRFuncType, GlobalValue::ExternalLinkage, composedName, metadata->currentModule);
}

Value* LgsPrint::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}
