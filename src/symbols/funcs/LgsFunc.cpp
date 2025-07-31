#include "funcs/LgsFunc.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "stmts/LgsReturn.h"
#include "types/LgsFuncType.h"
#include "utils/LgsUtils.h"

void LgsFunc::generateIR(LgsCodeGen* codeGen) {
    codeGen->stack.enterScope(FUNC_SCOPE, this);
    codeGen->startFuncBlock();
    stmtBlock->createIRValue(codeGen);
    if (!codeGen->lastInstTerminator()) {
        codeGen->builder.CreateRetVoid();
    }
    codeGen->stack.exitScope();
}

Value* LgsFunc::createIRValue(LgsCodeGen* codeGen) {
    codeGen->savedIP = codeGen->builder.saveIP();
    generateIR(codeGen);
    codeGen->builder.restoreIP(codeGen->savedIP);
    return getIRFunc(codeGen);
}

Function* LgsFunc::getIRFunc(LgsCodeGen* codeGen) {
    const auto funcIRName = funcType->getName();
    auto IRFunc = codeGen->IRModule->getFunction(funcIRName);
    if (IRFunc) return IRFunc;
    const auto type = funcType->getIRType(codeGen);
    const auto funcTy = cast<FunctionType>(type);
    auto func = codeGen->IRModule->getOrInsertFunction(funcIRName, funcTy);
    IRFunc = cast<Function>(func.getCallee());
    if (funcType->params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (int i = funcType->isStatic; i < funcType->params.size(); ++i) {
        auto& param = funcType->params[i];
        param.setIRValue(args);
        args->setName(param.name);
        args++;
    }
    return IRFunc;
}

Value* LgsFunc::getIRArg(LgsCodeGen* codeGen, LgsExpr* arg) {
    const auto v = arg->getIRValue(codeGen);
    if (isa<GlobalVariable>(v) || isa<LoadInst>(v)) return v;
    if (isa<Argument>(v) && v->getType()->isIntegerTy()) return v;
    const auto ty = arg->type->getIRType(codeGen);
    if (arg->type->isPrimitive && !arg->isConstant) {
        return codeGen->builder.CreateLoad(ty, v);
    }
    return v;
}

Value* LgsFunc::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    if (funcType->hasDefaults) assert(0);
    for (int i = funcType->isStatic; i < args.size(); ++i) {
        auto arg = getIRArg(codeGen, args[i]);
        IRArgs.push_back(arg);
    }
    return callIR(codeGen, IRArgs);
}

Value* LgsFunc::callIR(LgsCodeGen* codeGen, const vector<Value*>& args) {
    if (IRValue) {
        const auto funcTypeIR = funcType->getIRType(codeGen);
        const auto IRFuncType = cast<FunctionType>(funcTypeIR);
        return codeGen->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(codeGen);
    return codeGen->builder.CreateCall(IRFunc, args);
}

PHINode* LgsFunc::cleanupExprs(LgsCodeGen* codeGen) {
    PHINode* phiNode;
    auto& builder = builder;
    if (funcType->rt->isBig) {
        phiNode = builder.CreatePHI(codeGen->ptrTy(), returnExprs.size());
    } else {
        const auto IRReturnType = funcType->rt->getIRType(codeGen);
        phiNode = builder.CreatePHI(IRReturnType, returnExprs.size());
    }
    for (const auto expr : returnExprs) {
        const auto exprIR = expr->expr->getIRValue(codeGen);
        phiNode->addIncoming(exprIR, expr->parentBlock);
    }
    return phiNode;
}

string LgsFunc::prettyName() {
    return funcType->prettyName();
}

string LgsFunc::format(string& tabs) {
    stringstream str;
    str << funcType->name << "(";
    for (int i = funcType->isMethod; i < funcType->params.size(); ++i) {
        auto param = funcType->params[i];
        str << param.format(tabs);
        if (i != funcType->params.size() - 1) {
            str << ", ";
        }
    }
    str << ")";
    if (funcType->name != LOGOS_MAIN_FUNC_NAME) {
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
