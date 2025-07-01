#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtBlock.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"
#include "utils/LgsUtils.h"

void LgsFunc::generateIR(LgsModule* runtime) {
    runtime->stack.enterFunc(this);
    runtime->IRFunc = getIRFunc(runtime);
    startFuncBlock(runtime);
    stmtBlock->createIRValue(runtime);
    if (funcType->rt->isVoid) {
        if (!hasTerminator(runtime)) {
            runtime->builder.CreateRetVoid();
        }
    }
    runtime->IRFunc = nullptr;
    runtime->stack.exitFunc();
}

Type* LgsFunc::getIRFuncType(LLVMContext& context) {
    return funcType->getIRType(context);
}

Value* LgsFunc::createIRValue(LgsModule* runtime) {
    runtime->savedIP = runtime->builder.saveIP();
    generateIR(runtime);
    runtime->builder.restoreIP(runtime->savedIP);
    return getIRFunc(runtime);
}

Function* LgsFunc::getIRFunc(LgsModule* runtime) {
    const auto funcIRName = funcType->getIRName();
    auto IRFunc = runtime->IRModule->getFunction(funcIRName);
    if (IRFunc) return IRFunc;
    const auto funcTy = dyn_cast<FunctionType>(getIRFuncType(runtime->context));
    auto func = runtime->IRModule->getOrInsertFunction(funcIRName, funcTy);
    IRFunc = dyn_cast<Function>(func.getCallee());
    if (funcType->isSwapReturn) {
        setBigObjAttrs(*IRFunc);
    }
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

Value* LgsFunc::call(LgsModule* runtime, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    if (funcType->hasDefaults) assert(0);
    for (int i = funcType->isStaticMethod; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argType = arg->type->getIRType(runtime->context);
        auto argValue = arg->getIRValue(runtime);
        if (shouldLoadIRArg(argValue, arg)) {
            argValue = runtime->builder.CreateLoad(argType, argValue);
        }
        IRArgs.push_back(argValue);
    }
    return callIR(runtime, IRArgs);
}

Value* LgsFunc::callIR(LgsModule* runtime, const vector<Value*>& args) {
    if (IRValue) {
        const auto IRFuncType = cast<FunctionType>(funcType->rt->getIRType(runtime->context));
        return runtime->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(runtime);
    if (funcType->isSwapReturn) {
        const auto paramIRType = getReturnSwapParam().type->getIRType(runtime->context);
        const auto rv = runtime->builder.CreateAlloca(paramIRType);
        vector finalArgs(args.begin(), args.end());
        finalArgs.insert(finalArgs.begin() + funcType->returnParamIndex, rv);
        runtime->builder.CreateCall(IRFunc, finalArgs);
        return rv;
    }
    return runtime->builder.CreateCall(IRFunc, args);;
}

void LgsFunc::setBigObjAttrs(Function& IRFunc) const {
    const auto paramIRType = getReturnSwapParam().type->getIRType(IRFunc.getContext());
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::StructRet, paramIRType));
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::Writable));
    IRFunc.addParamAttr(funcType->returnParamIndex, Attribute::get(IRFunc.getContext(), Attribute::NoAlias));
}

LgsParam& LgsFunc::getReturnSwapParam() const {
    if (!funcType->isSwapReturn) assert(0);
    if (funcType->returnParamIndex > funcType->params.size()) assert(0);
    return funcType->params[funcType->returnParamIndex];
}

void LgsFunc::swapReturnIfNeeded() const {
    if (funcType->rt->isPrimitive) return;
    auto isEqual = true;
    // Check if there are different return expressions to check if a swap is possible
    for (const auto expr1 : returnExprs) {
        for (const auto expr2 : returnExprs) {
            if (expr1 == expr2) continue;
            if (expr1->equals(expr2)) continue;
            isEqual = false;
            break;
        }
    }
    if (funcType->isBigType && isEqual) {
        funcType->isSwapReturn = true;
        funcType->returnParamIndex = funcType->isMethod && !funcType->isStaticMethod;
        funcType->params.insert(funcType->params.begin(), LgsParam(funcType->rt));
        funcType->rt = &LGS_VOID;
    }
}

void LgsFunc::setExceptionFuncs(LgsModule* runtime) const {
    auto& builder = runtime->builder;
    auto ptrTy = builder.getPtrTy();
    const auto voidTy = builder.getVoidTy();
    const auto persFnType = FunctionType::get(builder.getInt32Ty(), true);
    const auto module = runtime->IRModule;
    auto personalityFunc = module->getOrInsertFunction("__gxx_personality_v0", persFnType);
    const auto cxaAlloc = module->getOrInsertFunction("__cxa_allocate_exception", FunctionType::get(ptrTy, { builder.getInt64Ty() }, false));
    const auto cxaThrow = module->getOrInsertFunction("__cxa_throw", FunctionType::get(voidTy, { ptrTy, ptrTy, ptrTy }, false));
    const auto cxaBeginCatch = module->getOrInsertFunction("__cxa_begin_catch", FunctionType::get(voidTy, { ptrTy }, false));
    const auto cxaEndCatch = module->getOrInsertFunction( "__cxa_end_catch", FunctionType::get(voidTy, {}, false));

    const auto normalBlock = BasicBlock::Create(runtime->context, "normal");
    const auto catchBlock = BasicBlock::Create(runtime->context, "catch");

    const auto alloc = builder.CreateCall(cxaAlloc, {builder.getInt64(4)});
    builder.CreateInvoke(cxaThrow, normalBlock, catchBlock, {alloc, Constant::getNullValue(ptrTy), Constant::getNullValue(ptrTy)});
    startBlock(runtime, normalBlock);
    builder.CreateRetVoid();

    startBlock(runtime, catchBlock);
    const auto landingPad = builder.CreateLandingPad(StructType::get(ptrTy, builder.getInt32Ty()), 1, "lpad");
    runtime->IRFunc->setPersonalityFn(cast<Function>(personalityFunc.getCallee()));
    landingPad->addClause(ConstantPointerNull::get(ptrTy));

    const auto exnPtr = builder.CreateExtractValue(landingPad, {0}, "exn_ptr");
    builder.CreateCall(cxaBeginCatch, exnPtr);
    builder.CreateCall(cxaEndCatch);
    builder.CreateRetVoid();
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
        str << funcType->rt->getIRName();
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