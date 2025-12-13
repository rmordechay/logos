#include "builtins/LgsPrint.h"
#include "exprs/LgsFuncCall.h"

Value* LgsPrint::call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    const std::vector<Type*> params = {cg.ptrTy(), cg.ptrTy()};
    const std::vector<Value*> IRArgs = {arg->type->getRTType(cg), arg->getPtrTo(cg)};
    return cg.callLgsFunc(name, cg.voidTy(), params, IRArgs);
}
