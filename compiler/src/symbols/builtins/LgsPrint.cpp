#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    if (arg->type->asBool()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        auto boolStr = cg.builder.CreateSelect(arg->IRValue, cg.getString(LgsBool::trueLiteral), cg.getString(LgsBool::falseLiteral));
        return cg.callPrintf({fmt, boolStr});
    }
    if (arg->type->asFloat()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(arg->IRValue, cg.doubleTy())});
    }
    if (arg->type->asStr()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateExtractValue(arg->IRValue, 1)});
    }
    if (arg->type->isInt || arg->type->asChar()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, arg->loadIR(cg)});
    }
    if (const auto enum_ = arg->type->asEnum()) {
        const auto fmt = cg.getString(arg->type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.getString(enum_->name)});
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
    const std::vector<Type*> params = {cg.i32Ty(), cg.ptrTy()};
    assert(arg->type->rtt != RTT_UNKNOWN);
    const std::vector<Value*> IRArgs = {cg.i32(arg->type->rtt), arg->IRValue};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}