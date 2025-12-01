#include "builtins/LgsPrint.h"
#include "exprs/LgsFuncCall.h"

Value* LgsPrint::call(LgsCgModule& cg, std::vector<LgsFuncArg>& args) {
    const auto arg = args.empty() ? funcType->params.front().expr : args.front().expr;
    return cg.callLgsFunc(name, cg.voidTy(), {cg.ptrTy(), cg.ptrTy()}, {
        arg->type->getRTType(cg), cg.getPtrTo(arg->IRValue)
    });
}
