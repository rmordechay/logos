#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/LgsFieldType.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    const auto type = arg->type;
    if (type->isFloat) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(arg->loadIR(cg), cg.doubleTy())});
    }
    if (type->asBool()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        const auto v = cg.builder.CreateSelect(arg->loadIR(cg), cg.getString(LgsBool::trueLiteral), cg.getString(LgsBool::falseLiteral));
        return cg.callPrintf({fmt, v});
    }
    if (type->asFieldType()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        const auto fieldName = LgsFieldType::loadRTName(cg, cg.loadPtr(arg->IRValue));
        return cg.callPrintf({fmt, fieldName});
    }
    if (type->isInt || type->asChar()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, loadAsInt(cg, arg->IRValue, type->getIRType(cg))});
    }
    if (type->asAny()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, arg->IRValue});
    }
    if (const auto enum_ = type->asEnum()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        const auto value = enum_->asIRStr(cg, arg->loadIR(cg));
        return cg.callPrintf({fmt, value});
    }
    assert(arg->type->rttKind != RTT_UNKNOWN);
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {type->getRTType(cg), arg->IRValue};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}
