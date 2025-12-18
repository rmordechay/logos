#include "funcs/LgsFunc.h"

#include "LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsFuncType.h"
#include "types/primitives/LgsVoid.h"
#include "LgsUtils.h"
#include "codegen/LgsCgModule.h"
#include "exprs/LgsArrayExpr.h"

#include <sstream>
#include <llvm/IR/Module.h>

struct LgsFuncArg;

Function* LgsFunc::getIRFunc(LgsCgModule& cg) {
    const auto funcName = funcType->getName();
    auto IRFunc = cg.IRModule->getFunction(funcName);
    if (IRFunc) return IRFunc;
    const auto type = funcType->getIRType(cg);
    const auto funcTy = llvm::cast<FunctionType>(type);
    IRFunc = cg.getFunc(funcName, funcTy);
    IRFunc->addFnAttr(Attribute::NoUnwind);
    if (funcType->params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (size_t i = 0; i < funcType->params.size(); ++i) {
        auto& param = funcType->params[i];
        args->setName(param.name);
        param.IRValue = args;
        args++;
    }
    return IRFunc;
}

void LgsFunc::initFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params, const uint32_t ops) {
    funcType = new LgsFuncType();
    funcType->name = name;
    funcType->rt = rt;
    funcType->setFuncOptions(ops);
    for (const auto& param : params) {
        funcType->params.push_back(param);
    }
    setType(funcType);
    if (funcType->isMethod) {
        funcType->params.front().isSelf = true;
    }
}

Value* LgsFunc::call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) {
    if (fn) return fn(cg, args);
    if (args.empty()) return callIR(cg, {});
    std::vector<Value*> IRArgs;
    if (funcType->isVariadic) return callWithVariadic(cg, args);
    const auto firstArgName = funcType->isMethod ? args[1].name : args.front().name;
    const auto isNamed = !args.empty() && firstArgName != "";
    if (isNamed) {
        std::unordered_map<std::string, LgsFuncArg*> argsByName;
        for (size_t i = 0; i < args.size(); ++i) {
            argsByName[args[i].name] = &args[i];
        }
        for (const auto& param : funcType->params) {
            assert(argsByName.contains(param.name));
            const auto arg = argsByName[param.name];
            IRArgs.emplace_back(arg->expr->IRValue);
        }
        assert(!funcType->hasDefaults);
    } else {
        for (const auto& arg : args) {
            IRArgs.emplace_back(arg.expr->IRValue);
        }
        if (funcType->hasDefaults) {
            const auto diff = funcType->params.size() - args.size() - 1;
            for (size_t i = diff; i < funcType->params.size(); ++i) {
                const auto& param = funcType->params[i];
                IRArgs.emplace_back(param.expr->IRValue);
            }
        }
    }
    return callIR(cg, IRArgs);
}

Value* LgsFunc::call(LgsCgModule& cg, const std::vector<LgsExpr*>& args) {
    std::vector<LgsFuncArg> funcArgs;
    for (const auto& arg : args) {
        funcArgs.push_back(LgsFuncArg(arg));
    }
    return call(cg, funcArgs);
}

Value* LgsFunc::callWithVariadic(LgsCgModule& cg, const std::vector<LgsFuncArg>& args) {
    std::vector<Value*> IRArgs;
    const auto variadicOffset = funcType->params.size() - 1;
    for (size_t i = 0; i < variadicOffset; ++i) {
        const auto arg = args[i];
        const auto& param = funcType->params[i];
        if (param.isSelf) {
            IRArgs.emplace_back(arg.expr->IRValue);
        } else {
            IRArgs.emplace_back(arg.expr->IRValue);
        }
    }
    if (!funcType->isExternal) {
        IRArgs.emplace_back(cg.usize(args.size()));
    }
    for (size_t i = variadicOffset; i < args.size(); ++i) {
        const auto arg = args[i];
        IRArgs.emplace_back(arg.expr->IRValue);
    }
    return callIR(cg, IRArgs);
}

Value* LgsFunc::callIR(LgsCgModule& cg, const std::vector<Value*>& args) {
    CallInst* rv = nullptr;
    if (IRValue) {
        const auto funcTypeIR = funcType->getIRType(cg);
        const auto IRFuncType = llvm::cast<FunctionType>(funcTypeIR);
        rv = cg.builder.CreateCall(IRFuncType, IRValue, args);
    } else {
        const auto IRFunc = getIRFunc(cg);
        rv = cg.builder.CreateCall(IRFunc, args);
    }
    return rv;
}

Value* LgsFunc::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsFunc::castImplicitly(LgsType* toType) {
    const auto otherFuncType = toType->asFuncType();
    if (!otherFuncType) return;
    if (funcType->isLambda) {
        if (funcType->params.empty() && otherFuncType->params.size() == 1) {
            auto otherParamType = otherFuncType->params.front().type;
            funcType->params.emplace_back(otherParamType, LGS_LAMBDA_IT_PARAM);
        }
    }
    for (size_t i = 0; i < funcType->params.size(); ++i) {
        if (funcType->params[i].type) continue;
        funcType->params[i].setType(otherFuncType->params[i].type);
    }
    if (!funcType->rt) {
        funcType->rt = otherFuncType->rt;
    }
}

std::string LgsFunc::getGenericName() const {
    std::stringstream str;
    str << "u_" << funcType->name;
    for (size_t i = funcType->isMethod; i < funcType->params.size(); ++i) {
        const auto& param = funcType->params[i];
        str << '_' << param.type->getName();
    }
    return str.str();
}

std::string LgsFunc::asText() {
    return funcType->pname();
}

void LgsFunc::hashNode(size_t& oldHash) {
    funcType->hashNode(oldHash);
    stmtsBlock->hashNode(oldHash);
}

void LgsFunc::createForeachFunc(LgsCgModule& cg) {
    if (cg.IRModule->getFunction(getGenericName())) return;
    // Save state
    cg.savedIP = cg.builder.saveIP();
    const auto originalFunc = cg.currentFunc;

    // Init
    cg.currentFunc = getIRFunc(cg);
    const auto& arrParam = funcType->params[0];
    const auto& callbackParam = funcType->params[1];
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, cg.currentFunc);
    const auto condBlock = cg.createBlock(BLOCK_LOOP_COND);
    const auto bodyBlock = cg.createBlock(BLOCK_LOOP_BODY);
    const auto exitBlock = cg.createBlock(BLOCK_LOOP_EXIT);
    cg.builder.SetInsertPoint(entryBlock);
    cg.callStackPush();

    const auto dArray = arrParam.type->asDArray();

    const auto iPtr = cg.builder.CreateAlloca(cg.sizeTy());
    const auto loopStart = cg.builder.CreateSExt(cg.sizeZero(), cg.sizeTy());
    cg.store(loopStart, iPtr);
    cg.builder.CreateBr(condBlock);

    // Condition
    cg.startBlock(condBlock);
    const auto iValue = cg.builder.CreateLoad(cg.sizeTy(), iPtr);
    const auto condition = cg.builder.CreateICmpSLT(iValue, dArray->lenIR(cg, arrParam.IRValue));
    cg.builder.CreateCondBr(condition, bodyBlock, exitBlock);

    // Body
    cg.startBlock(bodyBlock);
    auto element = dArray->getIRElement(cg, arrParam.IRValue, iValue);
    const auto ft = llvm::dyn_cast<FunctionType>(callbackParam.type->getIRType(cg));
    if (!dArray->baseType->passByRef) {
        element = cg.builder.CreateLoad(cg.ptrTy(), element);
    }
    cg.builder.CreateCall(ft, callbackParam.IRValue, {element});

    // Increment
    const auto inc = cg.builder.CreateAdd(iValue, cg.usize(1));
    cg.store(inc, iPtr);
    cg.builder.CreateBr(condBlock);

    // End func
    cg.startBlock(exitBlock);
    cg.callPopStack();
    cg.builder.CreateRetVoid();

    // Restore state
    cg.currentFunc = originalFunc;
    cg.builder.restoreIP(cg.savedIP);
    IRValue = getIRFunc(cg);
}

void LgsFunc::setDebugValue(LgsCgModule& cg) {
    const auto diBuilder = cg.debugger.diBuilder;
    const auto dbInt32 = funcType->rt->getDebugType(cg);
    const auto parameterTypes = diBuilder->getOrCreateTypeArray({dbInt32});
    const auto subroutine = diBuilder->createSubroutineType(parameterTypes);
    cg.debugger.subprogram = diBuilder->createFunction(
        cg.debugger.compileUnit,
        funcType->name,
        funcType->getName(),
        cg.debugger.diFile,
        location.lineStart,
        subroutine,
        location.lineStart,
        DINode::FlagPrototyped,
        DISubprogram::SPFlagDefinition
    );
    cg.IRModule->setFramePointer(FramePointerKind::All);
    const auto irFunc = getIRFunc(cg);
    irFunc->addFnAttr("frame-pointer", "all");
    irFunc->setSubprogram(cg.debugger.subprogram);
}

LgsFunc::~LgsFunc() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    freeType(funcType);
    funcType = nullptr;
}
