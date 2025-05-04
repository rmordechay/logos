#include "funcs/LgsFunc.h"
#include "LgsData.h"
#include "types/LgsObject.h"
#include "types/LgsVoid.h"

void LgsFunc::generateIRCode(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope(this);
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (getFuncType()->type->getName() == LgsVoid::name) {
        metadata->builder.CreateRetVoid();
    }
    metadata->lgsStack.exitScope();
}

string LgsFunc::format(string& indentStr) {
    stringstream str;
    const auto funcType = getFuncType();
    str << funcType->name << "(";
    for (int i = 0; i < funcType->params.size(); ++i) {
        auto param = funcType->params[i];
        str << param.format(indentStr);
        if (i != funcType->params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType->name != LOGOS_MAIN_FUNC) {
        str << funcType->type->getName();
    }
    str << stmtBlock->format(indentStr);
    return str.str();
}

json LgsFunc::asJSON() {
    json tree;
    const auto funcType = getFuncType();
    tree["name"] = funcType->name;
    tree["type"] = funcType->type->getName();
    tree["params"] = {};
    for (auto& param : funcType->params) {
        tree["params"].emplace_back(param.asJSON());
    }
    tree["stmts"] = stmtBlock->asJSON();
    return tree;
}

LgsFunc::~LgsFunc() {
    if (stmtBlock) {
        delete stmtBlock;
    }
}
