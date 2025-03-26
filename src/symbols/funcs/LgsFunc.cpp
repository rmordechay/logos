#include "funcs/LgsFunc.h"

void LgsFunc::setComposedName() {
    vector<string> paramTypeNames;
    for (const auto& param : params) {
        paramTypeNames.emplace_back(param->type->getName());
    }
    composedName = getComposedName(name, paramTypeNames);
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

string LgsFunc::getComposedName(const string& name, const vector<string>& paramTypeNames) {
    if (name == LOGOS_MAIN_FUNC) return name;
    auto composedName = name;
    for (int i = 0; i < paramTypeNames.size(); ++i) {
        composedName += "_" + paramTypeNames[i];
    }
    return composedName;
}

LgsFunc::~LgsFunc() {
    delete type;
    for (const auto param : params) {
        delete param;
    }
    delete stmtBlock;
}