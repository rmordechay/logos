#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>

#include "LgsDefinitions.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCodeGen& cg, std::vector<LgsFuncArg>& args) {
    cg.builder.CreateCall(generateFmtFunc(cg), {cg.emptyBuffer(), cg.i32(0), cg.null(), cg.null()});
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    if (arg->type->asFloat()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(arg->IRValue, cg.doubleTy())});
    }
    if (arg->type->asStr() || arg->type->asBool() || arg->type->asEnum() || arg->type->asEnumField()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        const auto value = arg->type->asIRStr(cg, arg->loadIR(cg));
        return cg.callPrintf({fmt, value});
    }
    if (arg->type->isInt || arg->type->asChar()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, arg->loadIR(cg)});
    }
    if (const auto vec = arg->type->asVec()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        std::vector<Value*> vecArgs = {fmt};
        const auto vecExpr = arg->loadIR(cg);
        for (size_t i = 0; i < vec->dimVec; ++i) {
            const auto element = cg.builder.CreateExtractValue(vecExpr, i);
            vecArgs.push_back(element);
        }
        return cg.callPrintf(vecArgs);
    }
    assert(arg->type->rtt != RTT_UNKNOWN);
    const std::vector<Type*> params = {cg.i32Ty(), cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {cg.i32(arg->type->rtt), arg->type->getRTType(cg), arg->IRValue};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}

Function* LgsPrint::generateFmtFunc(LgsCodeGen& cg) {
    const auto funcName = "formatElemen";
    if (const auto func = cg.IRModule->getFunction(funcName)) return func;
    const auto ft = cg.getFT(cg.voidTy(), {cg.ptrTy(), cg.i32Ty(), cg.ptrTy(), cg.ptrTy()});
    if (cg.mode == CG_MODE_SRC_CODE) return cg.getFunc(funcName, ft);
    const auto func = cg.getFunc(funcName, ft);
    const auto entryBlock = cg.createBlock(BLOCK_ENTRY, func);
    const auto defaultBlock = cg.createBlock(BLOCK_DEFAULT);
    cg.builder.SetInsertPoint(entryBlock);

    const auto buffer = func->getArg(0);
    const auto kind = func->getArg(1);
    const auto rtt = func->getArg(2);
    const auto value = func->getArg(3);
    cg.builder.CreateSwitch(kind, defaultBlock);

    cg.startBlock(defaultBlock);
    cg.builder.CreateRetVoid();
    return func;
}