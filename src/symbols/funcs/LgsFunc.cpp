#include "funcs/LgsFunc.h"

#include "LgsData.h"
#include "exprs/LgsExpr.h"
#include "funcs/LgsParam.h"
#include "types/LgsVoid.h"

string LgsFunc::format(string& indentStr) {
    stringstream ss;
    ss << signature.name << "(";
    for (int i = 0; i < signature.params.size(); ++i) {
        auto param = signature.params[i];
        ss << param.format(indentStr);
        if (i != signature.params.size() - 1) {
            ss << ", ";
        }
    }
    ss << ")";
    if (signature.name != LOGOS_MAIN_FUNC) {
        ss << signature.type->getName();
    }
    ss << stmtBlock->format(indentStr);
    return ss.str();
}

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
    // Without default params
    if (signature.params.size() == args.size()) {
        for (int i = signature.isStatic; i < args.size(); ++i) {
            const auto arg = args[i];
            const auto argValue = arg->getIRValue(metadata);
            argValues.emplace_back(argValue);
        }
    } else {
        // With default params
        for (int i = signature.isStatic; i < signature.params.size(); ++i) {
            LgsExpr* arg;
            if (i < args.size()) {
                arg = args[i];
            } else {
                arg = signature.params[i].expr;
                assert(arg);
            }
            const auto argValue = arg->getIRValue(metadata);
            argValues.emplace_back(argValue);
        }
    }
    return metadata->builder.CreateCall(IRFunc, argValues);;
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
