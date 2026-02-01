#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>

#include "LgsDefinitions.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCodeGen& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    if (arg->type->asFloat()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(arg->loadIR(cg), cg.doubleTy())});
    }
    if (arg->type->isInt || arg->type->asChar()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, arg->loadIR(cg)});
    }
    if (const auto enum_ = arg->type->asEnum()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        const auto value = enum_->asIRStr(cg, arg->loadIR(cg));
        return cg.callPrintf({fmt, value});
    }
    if (const auto vec = arg->type->asVec()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        std::vector<Value*> vecArgs = {fmt};
        const auto vecExpr = arg->loadIR(cg);
        for (size_t i = 0; i < vec->dimVec; ++i) {
            auto element = cg.builder.CreateExtractElement(vecExpr, i);
            if (vec->baseType->asFloat()) {
                element = cg.builder.CreateFPExt(element, cg.doubleTy());
            }
            vecArgs.push_back(element);
        }
        return cg.callPrintf(vecArgs);
    }
    assert(arg->type->rttKind != RTT_UNKNOWN);
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {arg->type->getRTType(cg), arg->IRValue};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}