#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsFuncType.h"
#include "../../../include/symbols/types/primitives/LgsVoid.h"
#include "utils/LgsUtils.h"
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Module.h>

Value* LgsFunc::call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args, const std::vector<LgsType*>& generics) {
    if (fn) return fn(cg, args);
    std::vector<Value*> IRArgs;
    if (funcType->isVariadic) {
        const auto variadicOffset = funcType->params.size() - 1;
        for (size_t i = 0; i < variadicOffset; ++i) {
            const auto arg = args[i];
            const auto& param = funcType->params[i];
            if (param.isSelf) {
                IRArgs.emplace_back(arg->IRValue);
            } else {
                IRArgs.emplace_back(arg->castToIR(cg, param.type));
            }
        }
        const auto& variadicParam = funcType->params[variadicOffset];
        IRArgs.emplace_back(cg.usize(args.size()));
        for (size_t i = variadicOffset; i < args.size(); ++i) {
            const auto arg = args[i];
            IRArgs.emplace_back(arg->castToIR(cg, variadicParam.type));
        }
    } else {
        for (size_t i = 0; i < args.size(); ++i) {
            const auto arg = args[i];
            const auto& param = funcType->params[i];
            if (param.isSelf) {
                IRArgs.emplace_back(arg->IRValue);
            } else {
                IRArgs.emplace_back(arg->castToIR(cg, param.type));
            }
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

Value* LgsFunc::callIR(LgsLLVMGen& cg, const std::vector<Value*>& args) {
    llvm::CallInst* rv = nullptr;
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

Value* LgsFunc::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Function* LgsFunc::getIRFunc(LgsLLVMGen& cg) {
    const auto funcName = getIRName();
    auto IRFunc = cg.IRModule->getFunction(funcName);
    if (IRFunc) return IRFunc;
    const auto type = funcType->getIRType(cg);
    const auto funcTy = llvm::cast<FunctionType>(type);
    IRFunc = cg.getFunc(funcName, funcTy);
    IRFunc->addFnAttr(llvm::Attribute::NoUnwind);
    if (funcType->params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (size_t i = 0; i < funcType->params.size(); ++i) {
        auto& param = funcType->params[i];
        if (param.isVariadic) {
            variadicCount = args;
            break;
        }
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
    if (funcType->isMethod) {
        funcType->parentName = params.front().type->getName();
    }
    for (const auto& param : params) {
        funcType->params.push_back(param);
    }
    setType(funcType);
}

void LgsFunc::completeType(LgsType* toType) {
    const auto otherFuncType = toType->asFuncType();
    if (!otherFuncType) return;
    for (size_t i = 0; i < funcType->params.size(); ++i) {
        if (funcType->params[i].type) continue;
        funcType->params[i].setType(otherFuncType->params[i].type);
    }
    if (!funcType->rt) {
        funcType->rt = otherFuncType->rt;
    }
}

BasicBlock* LgsFunc::getCleanupBlock(LgsLLVMGen& cg) {
    if (cleanupBlock) return cleanupBlock;
    cleanupBlock = cg.createBlock(BLOCK_NAME_CLEANUP);
    return cleanupBlock;
}

bool LgsFunc::needsCleanup() const {
    return !owners.empty() || !orphans.empty();
}

std::string LgsFunc::asText() {
    return funcType->pname();
}

std::string LgsFunc::getIRName() const {
    auto funcName = funcType->getName();
    if (funcType->isBuiltin && !funcType->isSysCall) {
        funcName = LGS_RUNTIME_NAMES_PREFIX + funcName;
    }
    return funcName;
}

void LgsFunc::hashNode(size_t& oldHash) {
    hashNodeString(oldHash, funcType->name);
}

LgsFunc* LgsFunc::cloneExpr() {
    const auto newFunc = new LgsFunc(*this);
    newFunc->funcType = funcType->clone()->asFuncType();
    newFunc->stmtsBlock = stmtsBlock->clone();
    return newFunc;
}

void LgsFunc::setDebugValue(LgsLLVMGen& cg) {
    const auto diBuilder = cg.debugger.diBuilder;
    const auto dbInt32 = funcType->rt->getDebugType(cg);
    const auto parameterTypes = diBuilder->getOrCreateTypeArray({dbInt32});
    const auto subroutine = diBuilder->createSubroutineType(parameterTypes);
    cg.debugger.diProgram = diBuilder->createFunction(
        cg.debugger.compileUnit,
        funcType->name,
        funcType->name,
        cg.debugger.diFile,
        location.lineStart,
        subroutine,
        location.lineStart,
        llvm::DINode::FlagPrototyped,
        DISubprogram::SPFlagDefinition
    );
    getIRFunc(cg)->setSubprogram(cg.debugger.diProgram);
    cg.builder.SetCurrentDebugLocation(getDebugLoc(cg));
}

LgsFunc::~LgsFunc() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
    freeType(funcType);
    funcType = nullptr;
}
