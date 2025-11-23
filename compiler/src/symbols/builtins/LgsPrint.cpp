#include "builtins/LgsPrint.h"
#include "exprs/LgsFuncCall.h"

Value* LgsPrint::call(LgsLLVMGen& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    const std::vector<Value*> IRArgs = {arg->type->getRTType(cg), cg.getPtrTo(arg->IRValue)};
    return cg.callLgsFunc(name, cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, IRArgs);
}
