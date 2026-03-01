#include "funcs/LgsFunc.h"

#include <llvm/IR/Module.h>
#include <assert.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/ADT/Twine.h>
#include <llvm/IR/Attributes.h>
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/DebugInfoMetadata.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/CodeGen.h>

#include "LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "types/LgsFuncType.h"
#include "types/iterables/LgsStr.h"
#include "codegen/LgsCodeGen.h"
#include "stmts/LgsReturn.h"
#include "LgsTokens.h"
#include "LgsType.h"
#include "stmts/LgsVarDec.h"

namespace llvm {
class FunctionType;
class Value;
}


std::string LgsFunc::asText() {
    return funcType->pname();
}

LgsExpr* LgsFunc::cast(LgsType* toType, const bool explicitly) {
    const auto otherFT = toType->asFuncType();
    if (!otherFT) return this;
    // Add 'it' if needed, else as normal params
    if (isLambda && funcType->params.empty() && otherFT->params.size() == 1) {
        auto itType = otherFT->params.front().type;
        funcType->params.emplace_back(itType, LGS_LAMBDA_IT_PARAM);
    } else {
        for (size_t i = 0; i < funcType->params.size(); ++i) {
            auto& thisParam = funcType->params[i];
            const auto newType = otherFT->params[i].type;
            if (thisParam.type) continue;
            thisParam.setType(newType);
        }
    }
    // Return type
    if (!funcType->rt) {
        funcType->rt = otherFT->rt;
    }
    if (!otherFT->typeParams.empty()) {
        funcType->typeParams.insert(funcType->typeParams.end(), otherFT->typeParams.begin(), otherFT->typeParams.end());
    }

    return this;
}

void LgsFunc::setType(LgsType* newType) {
    funcType = newType->asFuncType();
    type = funcType;
}

Function* LgsFunc::getIRFunc(LgsCodeGen& cg) {
    auto funcName = funcType->getName();
    if (isLambda) funcName += std::to_string(id);
    auto func = cg.IRModule->getFunction(funcName);
    if (func) return func;
    const auto type = funcType->getIRType(cg);
    const auto funcTy = llvm::cast<FunctionType>(type);
    func = cg.getFunc(funcName, funcTy);
    func->addFnAttr(Attribute::NoUnwind);
    if (funcType->params.empty() && !funcType->swapReturn) return func;
    auto args = func->arg_begin();
    if (funcType->swapReturn) {
        const auto sretAttr = Attribute::getWithStructRetType(cg.context, funcType->rt->getIRType(cg));
        func->addParamAttr(funcType->isMethod, sretAttr);
        args++;
    }
    for (size_t i = 0; i < funcType->params.size(); ++i) {
        auto& param = funcType->params[i];
        args->setName(param.name);
        param.IRValue = args;
        args++;
    }
    return func;
}

Value* LgsFunc::call(LgsCodeGen& cg, const std::vector<LgsVarDec>& args) {
    if (fn) return fn(cg, args);
    if (funcType->isExternal) return callExternal(cg, args);

    std::vector<Value*> IRArgs;
    if (funcType->isVariadic) {
        const auto variadicOffset = funcType->params.size() - 1;
        for (size_t i = 0; i < variadicOffset; ++i) {
            IRArgs.emplace_back(args[i].expr->IRValue);
        }
        IRArgs.emplace_back(cg.usize(args.size()));
        for (size_t i = variadicOffset; i < args.size(); ++i) {
            IRArgs.emplace_back(args[i].expr->IRValue);
        }
        return callIR(cg, IRArgs);
    }

    std::string firstArgName = "";
    if (funcType->isMethod) {
        firstArgName = args.size() > 1 ? args[1].name : "";
    } else {
        firstArgName = !args.empty() ? args[0].name : "";
    }
    if (firstArgName != "") {
        std::unordered_map<std::string, const LgsVarDec*> argsByName;
        for (const auto& arg : args) argsByName[arg.name] = &arg;
        for (const auto& param : funcType->params) {
            assert(argsByName.contains(param.name));
            IRArgs.emplace_back(argsByName[param.name]->expr->IRValue);
        }
    } else {
        for (const auto& arg : args) {
            IRArgs.emplace_back(arg.expr->IRValue);
        }
        if (funcType->hasDefaults) {
            for (size_t i = args.size(); i < funcType->params.size(); ++i) {
                IRArgs.emplace_back(funcType->params[i].expr->IRValue);
            }
        }
    }
    return callIR(cg, IRArgs);
}

Value* LgsFunc::callIR(LgsCodeGen& cg, const std::vector<Value*>& args) {
    auto argsList = args;
    Value* rv = nullptr;
    Value* sret = nullptr;
    if (funcType->swapReturn) {
        sret = cg.builder.CreateAlloca(funcType->rt->getIRType(cg));
        argsList.insert(argsList.begin() + funcType->isMethod, sret);
    }
    if (IRValue) {
        rv = cg.builder.CreateCall(funcType->getIRType(cg), IRValue, argsList);
    } else {
        rv = cg.builder.CreateCall(getIRFunc(cg), argsList);
    }
    return sret ? sret : rv;
}

Value* LgsFunc::callExternal(LgsCodeGen& cg, const std::vector<LgsVarDec>& args) {
    std::vector<Value*> IRArgs;
    for (const auto& arg : args) {
        if (const auto s = arg.expr->type->asStr()) {
            IRArgs.emplace_back(s->loadIRData(cg, arg.expr->IRValue));
        } else {
            IRArgs.emplace_back(arg.expr->IRValue);
        }
    }
    return callIR(cg, IRArgs);
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

void LgsFunc::setDebugValue(LgsCodeGen& cg) {
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

void LgsFunc::hashNode(size_t& oldHash) {
    funcType->hashNode(oldHash);
    stmtsBlock->hashNode(oldHash);
}

void LgsFunc::inferRetType() const {
    if (funcType->rt || returnStmts.empty()) return;
    std::vector<LgsExpr*> exprs;
    exprs.reserve(returnStmts.size());
    for (const auto& stmt : returnStmts) exprs.push_back(stmt->expr);
    funcType->rt = inferType(exprs);;
}

LgsFunc* LgsFunc::clone() const {
    const auto newFunc = new LgsFunc(*this);
    newFunc->setType(new LgsFuncType(*funcType));
    if (funcType->rt) newFunc->funcType->rt = funcType->rt->clone();
    if (stmtsBlock) newFunc->stmtsBlock = stmtsBlock->clone();
    return newFunc;
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
