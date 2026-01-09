#include "funcs/LgsFunc.h"

#include "LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsFuncType.h"
#include "types/primitives/LgsVoid.h"
#include "LgsUtils.h"
#include "codegen/LgsCgModule.h"
#include <sstream>
#include <llvm/IR/Module.h>

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

Value* LgsFunc::call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) {
    if (fn) return fn(cg, args);
    if (args.empty()) return callIR(cg, {});
    if (funcType->isVariadic) return callWithVariadic(cg, args);

    std::vector<Value*> IRArgs;
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

Value* LgsFunc::callIR(LgsCgModule& cg, const std::vector<Value*>& args) {
    Value* rv = nullptr;
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

Value* LgsFunc::loadIR(LgsCgModule& cg) {
    return IRValue;
}

void LgsFunc::initFunc(const std::string& name, LgsType* rt, const std::vector<LgsParam>& params, const uint32_t ops) {
    funcType = new LgsFuncType(name);
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

void LgsFunc::castImplicitly(LgsType* toType) {
    const auto otherFuncType = toType->asFuncType();
    if (!otherFuncType) return;

    // Add 'it' if needed, else as normal params
    if (isLambda && funcType->params.empty() && otherFuncType->params.size() == 1) {
        auto itType = otherFuncType->params.front().type;
        funcType->params.emplace_back(itType, LGS_LAMBDA_IT_PARAM);
    } else {
        for (size_t i = 0; i < funcType->params.size(); ++i) {
            auto& selfParam = funcType->params[i];
            if (selfParam.type) continue;
            selfParam.setType(otherFuncType->params[i].type);
        }
    }

    // Return type
    if (!funcType->rt) {
        funcType->rt = otherFuncType->rt;
    }
}

std::string LgsFunc::asText() {
    return funcType->pname();
}

void LgsFunc::setType(LgsType* newType) {
    LgsExpr::setType(newType);
    funcType = newType->asFuncType();
}

void LgsFunc::hashNode(size_t& oldHash) {
    funcType->hashNode(oldHash);
    stmtsBlock->hashNode(oldHash);
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
    freeType(type);
    type = nullptr;
    funcType = nullptr;
}
