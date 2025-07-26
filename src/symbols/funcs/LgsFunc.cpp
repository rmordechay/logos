#include "funcs/LgsFunc.h"

#include "builtin/LgsBuiltins.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "utils/LgsUtils.h"

void LgsFunc::generateIR(LgsModule* module) {
    module->stack.enterScope(FUNC_SCOPE, this);
    startFuncBlock(module);
    stmtBlock->createIRValue(module);
    createCleanupBlock(module);
    module->stack.exitScope();
}

Value* LgsFunc::createIRValue(LgsModule* module) {
    module->savedIP = module->builder.saveIP();
    generateIR(module);
    module->builder.restoreIP(module->savedIP);
    return getIRFunc(module);
}

Function* LgsFunc::getIRFunc(LgsModule* module) {
    const auto funcIRName = funcType->getName();
    auto IRFunc = module->IRModule->getFunction(funcIRName);
    if (IRFunc) return IRFunc;
    const auto type = funcType->getIRType(module);
    const auto funcTy = cast<FunctionType>(type);
    auto func = module->IRModule->getOrInsertFunction(funcIRName, funcTy);
    IRFunc = cast<Function>(func.getCallee());
    if (funcType->params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (int i = funcType->isStaticMethod; i < funcType->params.size(); ++i) {
        auto& param = funcType->params[i];
        param.setIRValue(args);
        args->setName(param.name);
        args++;
    }
    return IRFunc;
}

Value* LgsFunc::call(LgsModule* module, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    if (funcType->hasDefaults) assert(0);
    for (int i = funcType->isStaticMethod; i < args.size(); ++i) {
        const auto arg = args[i];
        auto argValue = arg->getIRValue(module);
        IRArgs.push_back(argValue);
    }
    return callIR(module, IRArgs);
}

Value* LgsFunc::callIR(LgsModule* module, const vector<Value*>& args) {
    if (IRValue) {
        const auto funcTypeIR = funcType->getIRType(module);
        const auto IRFuncType = cast<FunctionType>(funcTypeIR);
        return module->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(module);
    return module->builder.CreateCall(IRFunc, args);
}

void LgsFunc::addReturnExpr(LgsModule* module, LgsExpr* rv) {
    if (rv) {
        auto pair = make_pair(module->builder.GetInsertBlock(), rv);
        returnExprs.emplace_back(pair);
    }
    module->builder.CreateBr(cleanupBlock);
}

void LgsFunc::createCleanupBlock(LgsModule* module) {
    if (!lastInstTerminator(module)) {
        module->builder.CreateBr(cleanupBlock);
    }
    startBlock(module, cleanupBlock);
    const auto IRReturnType = funcType->rt->getIRType(module);
    Value* rv = nullptr;
    if (returnExprs.size() == 1) {
        rv = returnExprs.front().second->getIRValue(module);
    } else if (returnExprs.size() > 1) {
        const auto phiNode = module->builder.CreatePHI(IRReturnType, returnExprs.size());
        for (auto [block, returnExpr] : returnExprs) {
            phiNode->addIncoming(returnExpr->getIRValue(module), block);
        }
        rv = phiNode;
    }
    freeFunc(module);
    if (rv) module->builder.CreateRet(rv);
    else module->builder.CreateRetVoid();
}

Value* LgsFunc::freeFunc(LgsModule* module) const {
    for (auto _ : allocatedExprs) {}
    return lgsPrint.call(module, {new LgsStrConst("cleanup: " + module->stack.currentFunc()->funcType->name)});
}

string LgsFunc::prettyName() {
    return funcType->prettyName();
}

string LgsFunc::format(string& tabs) {
    stringstream str;
    str << funcType->name << "(";
    for (int i = 0; i < funcType->params.size(); ++i) {
        auto param = funcType->params[i];
        str << param.format(tabs);
        if (i != funcType->params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType->name != LOGOS_MAIN_FUNC) {
        str << funcType->rt->getName();
    }
    str << stmtBlock->format(tabs);
    return str.str();
}

LgsFunc::~LgsFunc() {
    freeType(type);
    if (stmtBlock) {
        delete stmtBlock;
    }
}