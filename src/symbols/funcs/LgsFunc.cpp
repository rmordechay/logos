#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtBlock.h"
#include "exprs/LgsExpr.h"
#include "types/LgsArray.h"
#include "utils/LgsUtils.h"

void LgsFunc::generateIR(LgsModule* module) {
    module->stack.enterFunc(this);
    module->IRFunc = getIRFunc(module);
    startFuncBlock(module);
    stmtBlock->createIRValue(module);
    if (funcType->rt->isVoid) {
        if (!hasTerminator(module)) {
            module->builder.CreateRetVoid();
        }
    }
    module->IRFunc = nullptr;
    module->stack.exitFunc();
}

Type* LgsFunc::getIRFuncType(LLVMContext& context) {
    return funcType->getIRType(context);
}

Value* LgsFunc::createIRValue(LgsModule* module) {
    module->savedIP = module->builder.saveIP();
    generateIR(module);
    module->builder.restoreIP(module->savedIP);
    return getIRFunc(module);
}

Function* LgsFunc::getIRFunc(LgsModule* module) {
    const auto funcIRName = funcType->getIRName();
    auto IRFunc = module->IRModule->getFunction(funcIRName);
    if (IRFunc) return IRFunc;
    const auto funcTy = dyn_cast<FunctionType>(getIRFuncType(module->context));
    auto func = module->IRModule->getOrInsertFunction(funcIRName, funcTy);
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

Value* LgsFunc::call(LgsModule* module, const vector<LgsExpr*>& args) {
    vector<Value*> IRArgs;
    if (funcType->hasDefaults) assert(0);
    for (int i = funcType->isStaticMethod; i < args.size(); ++i) {
        const auto arg = args[i];
        const auto argType = arg->type->getIRType(module->context);
        auto argValue = arg->getIRValue(module);
        if (shouldLoadIRArg(argValue, arg)) {
            argValue = module->builder.CreateLoad(argType, argValue);
        }
        IRArgs.push_back(argValue);
    }
    return callIR(module, IRArgs);
}

Value* LgsFunc::callIR(LgsModule* module, const vector<Value*>& args) {
    if (IRValue) {
        const auto IRFuncType = cast<FunctionType>(funcType->rt->getIRType(module->context));
        return module->builder.CreateCall(IRFuncType, IRValue, args);
    }
    const auto IRFunc = getIRFunc(module);
    if (funcType->isSwapReturn) {
        const auto paramIRType = getReturnSwapParam().type->getIRType(module->context);
        const auto rv = module->builder.CreateAlloca(paramIRType);
        vector finalArgs(args.begin(), args.end());
        finalArgs.insert(finalArgs.begin() + funcType->returnParamIndex, rv);
        module->builder.CreateCall(IRFunc, finalArgs);
        return rv;
    }
    return module->builder.CreateCall(IRFunc, args);;
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

void LgsFunc::setExceptionFuncs(LgsModule* module) const {
    auto& builder = module->builder;
    auto ptrTy = builder.getPtrTy();
    const auto voidTy = builder.getVoidTy();
    const auto persFnType = FunctionType::get(builder.getInt32Ty(), true);
    const auto IRModule = module->IRModule;
    auto personalityFunc = IRModule->getOrInsertFunction("__gxx_personality_v0", persFnType);
    const auto cxaAlloc = IRModule->getOrInsertFunction("__cxa_allocate_exception", FunctionType::get(ptrTy, { builder.getInt64Ty() }, false));
    const auto cxaThrow = IRModule->getOrInsertFunction("__cxa_throw", FunctionType::get(voidTy, { ptrTy, ptrTy, ptrTy }, false));
    const auto cxaBeginCatch = IRModule->getOrInsertFunction("__cxa_begin_catch", FunctionType::get(voidTy, { ptrTy }, false));
    const auto cxaEndCatch = IRModule->getOrInsertFunction( "__cxa_end_catch", FunctionType::get(voidTy, {}, false));

    const auto normalBlock = BasicBlock::Create(module->context, "normal");
    const auto catchBlock = BasicBlock::Create(module->context, "catch");

    const auto alloc = builder.CreateCall(cxaAlloc, {builder.getInt64(4)});
    builder.CreateInvoke(cxaThrow, normalBlock, catchBlock, {alloc, Constant::getNullValue(ptrTy), Constant::getNullValue(ptrTy)});
    startBlock(module, normalBlock);
    builder.CreateRetVoid();

    startBlock(module, catchBlock);
    const auto landingPad = builder.CreateLandingPad(StructType::get(ptrTy, builder.getInt32Ty()), 1, "lpad");
    module->IRFunc->setPersonalityFn(cast<Function>(personalityFunc.getCallee()));
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