#include "funcs/LgsPrint.h"

Value* LgsPrint::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto type = args[0]->type;
    FunctionCallee func;
    if (dynamic_cast<LgsInt*>(type)) {
        func = metadata->currentModule->getOrInsertFunction(IRNameString, funcTypeString);
    } else if (dynamic_cast<LgsFloat*>(type)) {
        func = metadata->currentModule->getOrInsertFunction(IRNameFloat, funcTypeFloat);
    } else if (dynamic_cast<LgsChar*>(type)) {
        func = metadata->currentModule->getOrInsertFunction(IRNameFloat, funcTypeFloat);
    } else {
        func = metadata->currentModule->getOrInsertFunction(IRNameInt, funcTypeInt);
    }
    auto argValue = args[0]->getIRValue(metadata);
    return metadata->builder.CreateCall(func, {argValue});
}

string LgsPrint::buildFuncName() const {
    auto IRName = name + "_" + type->getName();
    for (int i = 1; i < params.size(); ++i) {
        IRName += "_" + params[i]->type->getName();
    }
    return IRName;
}

Value* LgsPrint::createIRValue(CodeGenMetadata* metadata) {
    return nullptr;
}
