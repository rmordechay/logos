#include "funcs/LgsFunc.h"
#include "data/LgsDefinitions.h"
#include "stmts/LgsStmtsBlock.h"
#include "exprs/LgsExpr.h"
#include "exprs/constants/LgsStrConst.h"
#include "types/LgsFuncType.h"
#include "types/LgsVoid.h"
#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/Module.h>

Value* LgsFunc::call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
    if (fn) return fn(cg, args);
    std::vector<Value*> IRArgs;
    for (int i = 0; i < args.size(); ++i) {
        auto arg = args[i];
        const auto& param = funcType->params[i];
        Value* v = nullptr;
        const auto isSelf = funcType->isMethod && i == 0;
        if (!isSelf && !arg->type->equals(param.type)) {
            const auto cast = arg->castTo(param.type);
            if (cast != arg) freeExpr(arg);
            arg = cast;
        }
        v = arg->IRValue;
        IRArgs.emplace_back(v);
    }

    if (funcType->hasDefaults()) {
        const auto diff = funcType->params.size() - args.size();
        for (int i = diff; i < funcType->params.size(); ++i) {
            const auto& param = funcType->params[i];
            IRArgs.emplace_back(param.expr->IRValue);
        }
    }

    return callIR(cg, IRArgs);
}

Value* LgsFunc::callIR(LgsLLVMGen& cg, const std::vector<Value*>& args) {
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
    IRFunc->addFnAttr(Attribute::NoUnwind);
    if (funcType->params.empty()) return IRFunc;
    auto args = IRFunc->arg_begin();
    for (int i = 0; i < funcType->params.size(); ++i) {
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
    if (funcType->isMethod) {
        funcType->parentName = params.front().type->getName();
    }
    for (const auto& param : params) {
        funcType->params.push_back(param);
    }
    type = funcType;
}

void LgsFunc::completeType(LgsType* toType) {
    const auto otherFuncType = toType->asFuncType();
    if (!otherFuncType) return;
    for (int i = 0; i < funcType->params.size(); ++i) {
        if (funcType->params[i].type) continue;
        funcType->params[i].type = otherFuncType->params[i].type;
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

std::string LgsFunc::pname() {
    return funcType->pname();
}

std::string LgsFunc::getIRName() const {
    auto funcName = funcType->getName();
    if (funcType->isBuiltin && !funcType->isSysCall) {
        funcName = LGS_RUNTIME_NAMES_PREFIX + funcName;
    }
    return funcName;
}

json::value LgsFunc::asJSON() {
    json::object obj;
    obj["funcType"] = funcType->asJSON();
    obj["stmtsBlock"] = stmtsBlock->asJSON();
    return obj;
}

void LgsFunc::setDebugValue(LgsLLVMGen& cg) {
    const auto diBuilder = cg.diBuilder;
    const auto dbInt32 = funcType->rt->getDebugType(cg);
    const auto parameterTypes = diBuilder->getOrCreateTypeArray({dbInt32});
    const auto subroutine = diBuilder->createSubroutineType(parameterTypes);
    cg.diProgram = diBuilder->createFunction(
        cg.compileUnit,
        funcType->name,
        "",
        cg.diFile,
        location.lineStart,
        subroutine,
        location.lineStart
    );
    getIRFunc(cg)->setSubprogram(cg.diProgram);
    cg.builder.SetCurrentDebugLocation(getDebugLoc(cg));
}

LgsFunc::~LgsFunc() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
}
