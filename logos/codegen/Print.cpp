#include "Print.h"

void Print::generateCode(IRBuilder<>& builder, Module* module, std::map<std::string, Function*>* functions, map<string, Value*>* symbolTable) {
    const auto funcName = funcCallExpr->name;
    const auto printfFunc = (*functions)[funcName];

    auto formatStr = builder.CreateGlobalStringPtr("Printing: %d\n");
    const auto intAlloc = (*symbolTable)["a"];
    auto loadInst = builder.CreateLoad(builder.getInt32Ty(), intAlloc);
    builder.CreateCall(printfFunc, {formatStr, loadInst});
}
