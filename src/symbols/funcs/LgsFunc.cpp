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
    if (funcType->rt->isBig && returnExprs.size() > 1) {
        allocReturnStructs(codeGen);
    }
    stmtBlock->createIRValue(codeGen);
    createCleanupBlock(codeGen);
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

// bool shouldLoadIRArg(Value* value) {
//     if (isa<GlobalVariable>(value) || isa<LoadInst>(value)) return false;
//     if (const auto alloca = dyn_cast<AllocaInst>(value)) {
//         const auto allocatedType = alloca->getAllocatedType();
//         return !allocatedType->isStructTy() && !allocatedType->isArrayTy();
//     }
//     if (value->getType()->isIntegerTy() || value->getType()->isFloatingPointTy()) {
//         return false;
//     }
//     if (const auto gep = dyn_cast<GetElementPtrInst>(value)) {
//         const auto source = gep->getSourceElementType();
//         const auto results = gep->getResultElementType();
//         const auto isArrayTy = source->isArrayTy();
//         const auto isByteTy = results && results->isIntegerTy(8);
//         return !isArrayTy || !isByteTy;
//     }
//     if (isa<ConstantExpr>(value)) {
//         const auto constExpr = cast<ConstantExpr>(value);
//         return constExpr->getOpcode() == Instruction::GetElementPtr;
//     }
//     if (isa<Function>(value)) return false;
//     return true;
// }

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

void LgsFunc::createCleanupBlock(LgsCodeGen* codeGen) const {
    if (!codeGen->lastInstTerminator()) codeGen->builder.CreateBr(cleanupBlock);
    codeGen->startBlock(cleanupBlock);
    Value* rv = nullptr;
    if (returnExprs.size() == 1) {
        rv = returnExprs.front()->expr->getIRValue(codeGen);
    } else if (returnExprs.size() > 1) {
        rv = cleanupExprs(codeGen);
    }
    for (const auto expr : heapAllocExprs) {
        expr->type->freeValue(codeGen, expr->getIRValue(codeGen));
    }
    codeGen->callPopStack();
    if (rv) {
        codeGen->builder.CreateRet(rv);
    }
}

PHINode* LgsFunc::cleanupExprs(LgsCodeGen* codeGen) const {
    PHINode* phiNode;
    if (funcType->rt->isBig) {
        phiNode = codeGen->builder.CreatePHI(codeGen->ptrTy(), returnExprs.size());
    } else {
        const auto IRReturnType = funcType->rt->getIRType(codeGen);
        phiNode = codeGen->builder.CreatePHI(IRReturnType, returnExprs.size());
    }
    for (const auto returnExpr : returnExprs) {
        const auto exprIR = returnExpr->expr->getIRValue(codeGen);
        phiNode->addIncoming(exprIR, returnExpr->parentBlock);
        codeGen->printStr(returnExpr->parentBlock->getName().str() + ": ");
        codeGen->printPtr(exprIR);
    }
    codeGen->printPtr(phiNode);
    return phiNode;
}

void LgsFunc::allocReturnStructs(LgsCodeGen* codeGen) const {
    for (const auto expr : returnExprs) {
        const auto structType = StructType::get(codeGen->context, {codeGen->i1Ty(), codeGen->ptrTy()});
        expr->returnStruct = codeGen->builder.CreateAlloca(structType);
        expr->setReturnFlag(codeGen, false);
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
