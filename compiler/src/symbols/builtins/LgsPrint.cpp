#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/LgsFieldType.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCodeGen& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    const auto type = arg->type;
    if (type->asFloat()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(arg->loadIR(cg), cg.doubleTy())});
    }
    if (type->asBool()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        const auto v = cg.builder.CreateSelect(arg->loadIR(cg), cg.getString(LgsBool::trueLiteral), cg.getString(LgsBool::falseLiteral));;
        return cg.callPrintf({fmt, v});
    }
    if (type->asFieldType()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        const auto fieldName = LgsFieldType::loadRTName(cg, cg.loadPtr(arg->IRValue));
        return cg.callPrintf({fmt, fieldName});
    }
    if (type->isInt || type->asChar() || type->asAny()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, arg->loadIR(cg)});
    }
    if (const auto enum_ = type->asEnum()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        const auto value = enum_->asIRStr(cg, arg->loadIR(cg));
        return cg.callPrintf({fmt, value});
    }
    if (const auto vec = type->asVec()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
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
    const std::vector<Value*> IRArgs = {type->getRTType(cg), arg->IRValue};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}