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
    cleanup(codeGen, nullptr);
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

void LgsFunc::cleanup(LgsCodeGen* codeGen, AllocaInst* returnExprsArr) const {
    codeGen->branchIfNeeded(cleanupBlock);
    codeGen->startBlock(cleanupBlock);
    Value* rv = nullptr;
    if (returnExprs.size() == 1) {
        rv = returnExprs.front()->expr->getIRValue(codeGen);
    } else if (returnExprs.size() > 1) {
        rv = cleanupExprs(codeGen, returnExprsArr);
    }
    codeGen->callPopStack();
    if (rv) codeGen->builder.CreateRet(rv);
}

PHINode* LgsFunc::cleanupExprs(LgsCodeGen* codeGen, AllocaInst* returnExprsArr) const {
    PHINode* phiNode;
    auto& builder = codeGen->builder;
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

    // Cleanup loop
    // const auto notNullBlock = codeGen->createBlock(BLOCK_NAME_NOT_NULL);
    // const auto blockLoopCond = codeGen->createBlock(BLOCK_NAME_CLEANUP_LOOP_COND);
    // const auto blockLoopBody = codeGen->createBlock(BLOCK_NAME_CLEANUP_LOOP_BODY);
    // const auto blockLoopExit = codeGen->createBlock(BLOCK_NAME_CLEANUP_LOOP_EXIT);
    // const auto blockLoopInc = codeGen->createBlock(BLOCK_NAME_CLEANUP_LOOP_INC);
    // const auto blockFreeElement = codeGen->createBlock(BLOCK_NAME_CLEANUP_FREE_ELEMENT);
    // const auto iPtr = builder.CreateAlloca(codeGen->i32Ty());
    // const auto upperBound = codeGen->i32(returnExprs.size());
    // builder.CreateStore(codeGen->i32Zero(), iPtr);
    // builder.CreateBr(blockLoopCond);
    //
    // // Cond
    // codeGen->startBlock(blockLoopCond);
    // auto iValue = builder.CreateLoad(codeGen->i32Ty(), iPtr);
    // const auto cond = builder.CreateICmpSLT(iValue, upperBound);
    // builder.CreateCondBr(cond, blockLoopBody, blockLoopExit);
    //
    // // Body
    // codeGen->startBlock(blockLoopBody);
    // const auto rsType = StructType::get(codeGen->context, {codeGen->i1Ty(), codeGen->ptrTy()});
    // const auto arrType = ArrayType::get(rsType, returnExprs.size());
    // const auto structPtr = builder.CreateInBoundsGEP(arrType, returnExprsArr, {codeGen->i32(0), iValue});
    // const auto flagPtr = builder.CreateStructGEP(rsType, structPtr, 0);
    // const auto flagValue = builder.CreateLoad(codeGen->i1Ty(), flagPtr);
    // builder.CreateCondBr(flagValue, blockLoopInc, blockFreeElement);
    //
    // // Free element
    // codeGen->startBlock(blockFreeElement);
    // const auto gep = builder.CreateStructGEP(rsType, structPtr, 1);
    // const auto value = builder.CreateLoad(codeGen->ptrTy(), gep);
    //
    // // const auto isNull = builder.CreateIsNull(value);
    // // builder.CreateCondBr(isNull, blockLoopInc, notNullBlock);
    // // codeGen->startBlock(notNullBlock);
    // funcType->rt->freeValue(codeGen, value);
    // builder.CreateBr(blockLoopInc);
    //
    // // Loop inc
    // codeGen->startBlock(blockLoopInc);
    // iValue = builder.CreateLoad(codeGen->i32Ty(), iPtr);
    // const auto inc = builder.CreateAdd(iValue, codeGen->i32(1));
    // builder.CreateStore(inc, iPtr);
    // builder.CreateBr(blockLoopCond);
    //
    // // Exit
    // codeGen->startBlock(blockLoopExit);
    return phiNode;
}

AllocaInst* LgsFunc::allocReturnStructs(LgsCodeGen* codeGen) const {
    if (!funcType->rt->isBig || returnExprs.size() <= 1) return nullptr;
    const auto structType = StructType::get(codeGen->context, {codeGen->i1Ty(), codeGen->ptrTy()});
    const auto arrType = ArrayType::get(structType, returnExprs.size());
    const auto returnExprsArr = codeGen->builder.CreateAlloca(arrType);
    for (int i = 0; i < returnExprs.size(); ++i) {
        const auto structPtr = codeGen->builder.CreateInBoundsGEP(arrType, returnExprsArr, {codeGen->i32(0), codeGen->i32(i)});
        returnExprs[i]->returnStructPtr = dyn_cast<GetElementPtrInst>(structPtr);
        returnExprs[i]->setReturnFlag(codeGen, false);
        returnExprs[i]->setReturnValue(codeGen, codeGen->null());
    }
    return returnExprsArr;
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
