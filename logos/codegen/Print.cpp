#include "Print.h"

void Print::generateCode(IRBuilder<>& builder, Module* module, std::map<std::string, Function*> functions) {
    const auto name = funcCallExpr->name;
    const auto printfFunc = functions[name];
    auto formatStr = builder.CreateGlobalStringPtr("Printing: %d\n");
    builder.CreateCall(printfFunc, {formatStr, ConstantInt::get(builder.getInt32Ty(), 5)});
}
