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

void LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope();
    if (!IRFunc) setIRFunc(metadata);
    metadata->logosStack.currentFunc = IRFunc;
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    metadata->logosStack.exitScope();
}

json LgsFunc::asJson() {
    json tree;
    tree["name"] = name;
    tree["returnType"] = type->getName();
    for (const auto& param : params) {
        tree["params"].emplace_back(param->asJson());
    }
    tree["stmts"] = stmtBlock->asJson();
    return tree;
}

LgsFunc::~LgsFunc() {
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}