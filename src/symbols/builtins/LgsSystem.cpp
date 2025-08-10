#include "builtins/LgsSystem.h"

Value* LgsSystemPid::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    const auto ft = FunctionType::get(codeGen->sizeTy(), false);
    const auto func = codeGen->IRModule->getOrInsertFunction("getpid", ft);
    return codeGen->builder.CreateCall(func);
}

Value* LgsSystemSleep::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    return codeGen->callSleep(args[1]->getIRValue(codeGen));
}

Value* LgsSystemExit::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    return codeGen->callExit(args[1]->getIRValue(codeGen));
}

Value* LgsSystemCwd::call(LgsCodeGen* codeGen, const vector<LgsExpr*>& args) {
    return codeGen->callCwd();
}
