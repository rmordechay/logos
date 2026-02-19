#include "builtins/LgsPrint.h"
#include <llvm/IR/Module.h>
#include "codegen/LgsCodeGen.h"
#include "exprs/LgsFuncCall.h"
#include "types/LgsEnum.h"
#include "types/LgsFieldType.h"
#include "types/LgsNullable.h"
#include "types/iterables/LgsVec.h"
#include "types/primitives/LgsBool.h"

Value* LgsPrint::call(LgsCodeGen& cg, const std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    const auto type = arg->type;
    auto v = arg->IRValue;
    if (type->isFloat) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.builder.CreateFPExt(v, cg.doubleTy())});
    }
    if (type->asBool()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        v = cg.builder.CreateSelect(v, cg.getString(LgsBool::trueLiteral), cg.getString(LgsBool::falseLiteral));
        return cg.callPrintf({fmt, v});
    }
    if (type->asFieldType()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        const auto fieldName = LgsFieldType::loadRTName(cg, cg.loadPtr(v));
        return cg.callPrintf({fmt, fieldName});
    }
    if (type->isInt || type->asChar()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, loadAsInt(cg, v, type->getIRType(cg))});
    }
    if (type->asAny()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, v});
    }
    if (const auto enum_ = type->asEnum()) {
        const auto fmt = cg.getString(type->fmtStr() + "\n");
        return cg.callPrintf({fmt, cg.getString(enum_->getName())});
    }
    if (type->asNullable()) {
        LgsStrBuilder sb(cg);
        type->asIRText(sb, v);
        sb.finalize();
        return cg.callPrintf("%s\n", {sb.buffer});
    }
    assert(arg->type->rttKind != RTT_UNKNOWN);
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {type->getRTType(cg), v};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}
