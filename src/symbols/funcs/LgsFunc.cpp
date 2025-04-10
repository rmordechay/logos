#include "funcs/LgsFunc.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsVoid.h"

void LgsFunc::createIRValue(CodeGenMetadata* metadata) {
    metadata->lgsStack.enterScope(this);
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
    metadata->lgsStack.exitScope();
}

Value* LgsFunc::call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) {
    const auto IRFunc = getIRFunc(metadata);
    vector<Value*> argValues;
    for (int i = signature.isStatic; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argValue = arg->getIRValue(metadata);
        argValues.emplace_back(argValue);
    }
    return metadata->builder.CreateCall(IRFunc, argValues);
}

Function* LgsFunc::getIRFunc(const CodeGenMetadata* metadata) {
    if (!IRFuncType) setIRFuncType();
    auto func = metadata->module->getOrInsertFunction(signature.IRName, IRFuncType);
    return dyn_cast<Function>(func.getCallee());
}

LgsFunc::~LgsFunc() {
    if (stmtBlock) {
        delete stmtBlock;
    }
}
