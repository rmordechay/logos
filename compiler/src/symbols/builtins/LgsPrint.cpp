#include "builtins/LgsPrint.h"
#include "exprs/LgsFuncCall.h"

Value* LgsPrint::call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    Value* v;
    if (arg->asStrConst()) {
        v = cg.allocaAndStore(cg.ptrTy(), arg->IRValue);
    } else {
        v = cg.getPtrTo(arg->IRValue);
    }
    const std::vector<Value*> IRArgs = {arg->type->getRTType(cg), v};
    return cg.callLgsFunc("", name, cg.voidTy(), params, IRArgs);
}
