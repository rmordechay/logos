#include "funcs/LgsFunc.h"

vector<string> LgsFunc::getParamTypeNames() const {
    vector<string> names;
    for (const auto& param : params) {
        names.emplace_back(param->type->getName());
    }
    return names;
}

string LgsFunc::getComposedName(const string& name, const vector<string>& paramTypeNames) {
    if (name == LOGOS_MAIN_FUNC) {
        return name;
    }
    auto composedName = name;
    for (int i = 0; i < paramTypeNames.size(); ++i) {
        composedName += "_" + paramTypeNames[i];
    }
    return composedName;
}

Value* LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    if (!IRFunc) setIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;
    startBlock(metadata, entryBlock);
    stmtBlock->getIRValue(metadata);
    metadata->logosStack.exitScope();
    return IRFunc;
}

LgsFunc::~LgsFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}