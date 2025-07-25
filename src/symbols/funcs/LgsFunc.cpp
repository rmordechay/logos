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
    if (returnValue) {
        module->builder.CreateRet(returnValue);
    } else if (funcType->rt->isVoid) {
        module->builder.CreateRetVoid();
    }
    module->stack.exitScope(true);
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
    if (funcType->isSwapReturn) setBigObjAttrs(module, *IRFunc);
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
    if (funcType->isSwapReturn) {
        const auto paramIRType = getReturnSwapParam().type->getIRType(module);
        const auto rv = module->builder.CreateAlloca(paramIRType);
        vector finalArgs(args.begin(), args.end());
        finalArgs.insert(finalArgs.begin() + funcType->returnParamIndex, rv);
        module->builder.CreateCall(IRFunc, finalArgs);
        return rv;
    }
    return module->builder.CreateCall(IRFunc, args);;
}

void LgsFunc::setBigObjAttrs(LgsModule* module, Function& IRFunc) const {
    const auto paramIRType = getReturnSwapParam().type->getIRType(module);
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::StructRet, paramIRType));
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::Writable));
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::NoAlias));
}

void LgsFunc::createCleanupBlock(LgsModule* module) const {
    // if (!lastInstTerminator(module)) branchToCleanup(module);
    // startBlock(module, cleanupBlock);
    // lgsPrint.call(module, {new LgsStrConst("cleanup: " + module->stack.currentFunc->funcType->name)});
}

void LgsFunc::branchToCleanup(LgsModule* module) const {
    // module->builder.CreateBr(cleanupBlock);
}

LgsParam& LgsFunc::getReturnSwapParam() const {
    if (!funcType->isSwapReturn) assert(0);
    if (funcType->returnParamIndex > funcType->params.size()) assert(0);
    return funcType->params[funcType->returnParamIndex];
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