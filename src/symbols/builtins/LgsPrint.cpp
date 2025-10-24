#include "builtins/LgsPrint.h"
#include "exprs/constants/LgsStrConst.h"

Value* LgsPrint::call(LgsLLVMGen& cg, const std::vector<LgsExpr*>& args) {
    const auto arg = args.front();
    assert(arg->IRValue);
    const std::vector<Value*> IRArgs = {
        cg.i32(arg->type->getRTType()),
        cg.getPtrTo(arg->IRValue),
    };
    return cg.callLgsFunc(name, cg.voidTy(), {cg.i32Ty(), cg.ptrTy()}, IRArgs);
}