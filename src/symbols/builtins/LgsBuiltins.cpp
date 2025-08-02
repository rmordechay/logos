#include  "builtins/LgsBuiltins.h"

Value* LgsPrint::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    const auto arg = args.front();
    const auto formatStr = arg->type->getStrFormatPart() + '\n';
    const auto IRArgs = {codeGen->getIRStr(formatStr), getIRArg(codeGen, arg)};
    return codeGen->callPrintf(IRArgs);
}

Value* LgsSizeOf::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    return codeGen->i64(args.front()->type->getSizeBytes());
}
