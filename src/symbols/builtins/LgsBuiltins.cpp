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

Value* LgsSystemPid::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    const auto ft = FunctionType::get(codeGen->sizeTy(), false);
    const auto func = codeGen->IRModule->getOrInsertFunction("getpid", ft);
    return codeGen->builder.CreateCall(func);
}

Value* LgsSystemSleep::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    const auto ft = FunctionType::get(codeGen->voidTy(), {codeGen->i32Ty()}, false);
    const auto func = codeGen->IRModule->getOrInsertFunction("exit", ft);
    return codeGen->builder.CreateCall(func, {args[1]->getIRValue(codeGen)});
}

Value* LgsSystemExit::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    return codeGen->callExit(args[1]->getIRValue(codeGen));
}
