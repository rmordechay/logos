#include "funcs/LgsFunc.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsVoid.h"

void LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->logosStack.enterScope(this);
    const auto IRFunc = getIRFunc(metadata);
    auto args = IRFunc->arg_begin();
    for (auto& param : signature.params) {
        param.setIRValue(args);
        args++->setName(param.name);
    }
    startBlock(metadata, entryBlock);
    stmtBlock->createIRValue(metadata);
    if (signature.type->getName() == LgsVoid::name) {
        metadata->builder.CreateRetVoid();
    }
    metadata->logosStack.exitScope(metadata);
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto IRFunc = getIRFunc(metadata);
    vector<Value*> argValues;
    const auto size = signature.isStatic ? 1 : 0;
    for (int i = size; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(IRFunc, argValues);
}

bool LgsFunc::equals(const LgsFuncSignature* otherSignature) const {
    if (signature.parentName != "" && otherSignature->parentName != "")
    if (signature.parentName != otherSignature->parentName) return false;
    if (signature.name != otherSignature->name) return false;
    if (signature.type->getName() != otherSignature->type->getName()) return false;
    if (signature.params.size() == 0) return true;
    for (size_t i = 0; i < signature.params.size() - 1; ++i) {
        auto thisTypeName = signature.params[i + 1].type->getName();
        auto otherTypeName = otherSignature->params[i].type->getName();
        if (thisTypeName != otherTypeName) return false;
    }
    return true;
}

Function* LgsFunc::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) setIRFuncType();
    auto func = metadata->module->getOrInsertFunction(signature.IRName, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
}

json LgsFunc::asJson() {
    json tree;
    tree["name"] = signature.name;
    tree["returnType"] = signature.type->getName();
    for (auto& param : signature.params) {
        tree["params"].emplace_back(param.asJson());
    }
    tree["stmts"] = stmtBlock->asJson();
    return tree;
}

LgsFunc::~LgsFunc() {
    if (stmtBlock) {
        delete stmtBlock;
    }
}
