#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/unary/constants/LgsStrConst.h"
#include "types/LgsVoid.h"
#include "utils/LgsIRUtils.h"
#include "utils/LgsUtils.h"

void LgsFunc::generateIR(LgsModule* module) {
    module->stack.enterScope(FUNC_SCOPE, this);
    startFuncBlock(module);
    stmtBlock->createIRValue(module);
    createCleanupBlock(module);
    if (!lastInstTerminator(module)) {
        module->builder.CreateRetVoid();
    }
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
    for (int i = funcType->isStatic; i < funcType->params.size(); ++i) {
        auto& param = funcType->params[i];
        param.setIRValue(args);
        args->setName(param.name);
        args++;
    }
    return IRFunc;
}

bool shouldLoadIRArg(Value* value) {
    if (isa<GlobalVariable>(value) || isa<LoadInst>(value)) return false;
    if (const auto alloca = dyn_cast<AllocaInst>(value)) {
        const auto allocatedType = alloca->getAllocatedType();
        return !allocatedType->isStructTy() && !allocatedType->isArrayTy();
    }
    if (value->getType()->isIntegerTy() || value->getType()->isFloatingPointTy()) {
        return false;
    }
    if (const auto gep = dyn_cast<GetElementPtrInst>(value)) {
        const auto source = gep->getSourceElementType();
        const auto results = gep->getResultElementType();
        const auto isArrayTy = source->isArrayTy();
        const auto isByteTy = results && results->isIntegerTy(8);
        return !isArrayTy || !isByteTy;
    }
    if (isa<ConstantExpr>(value)) {
        const auto constExpr = cast<ConstantExpr>(value);
        return constExpr->getOpcode() == Instruction::GetElementPtr;
    }
    if (isa<Function>(value)) return false;
    return true;
}

Value* LgsFunc::getIRArg(LgsModule* module, LgsExpr* arg) {
    const auto v = arg->getIRValue(module);
    if (isa<GlobalVariable>(v) || isa<LoadInst>(v)) return v;
    if (isa<Argument>(v) && v->getType()->isIntegerTy()) return v;
    const auto ty = arg->type->getIRType(module);
    if (arg->type->isPrimitive && !arg->isConstant) {
        return module->builder.CreateLoad(ty, v);
    }
    return v;
}

Value* LgsFunc::call(LgsModule* module, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    if (funcType->hasDefaults) assert(0);
    for (int i = funcType->isStatic; i < args.size(); ++i) {
        auto arg = getIRArg(module, args[i]);
        IRArgs.push_back(arg);
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

void LgsFunc::createCleanupBlock(LgsModule* module) const {
    if (!lastInstTerminator(module)) {
        module->builder.CreateBr(cleanupBlock);
    }
    startBlock(module, cleanupBlock);
    const auto IRReturnType = funcType->rt->getIRType(module);
    Value* rv = nullptr;
    if (returnExprs.size() == 1) {
        rv = returnExprs.front()->getIRValue(module);
    } else if (returnExprs.size() > 1) {
        const auto phiNode = module->builder.CreatePHI(IRReturnType, returnExprs.size());
        for (const auto expr : returnExprs) {
            phiNode->addIncoming(expr->getIRValue(module), expr->parentBlock);
        }
        rv = phiNode;
    }
    freeAllocations(module);
    callPopStack(module);
    if (rv) {
        module->builder.CreateRet(rv);
    }
}

void LgsFunc::freeAllocations(LgsModule* module) const {
    for (const auto expr : allocatedExprs) {
        expr->free(module);
    }
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