#include "Print.h"

#include "types/LogosString.h"

void Print::generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const {
    const auto argStr = dynamic_cast<LogosString*>(left->logosType)->value;
    const auto argString = builder.CreateGlobalStringPtr("Printing: " + argStr);
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::getUnqual(builder.getInt8Ty()), true);
    const auto printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", module);
    auto formatStr = builder.CreateGlobalStringPtr("%s\n", "name");
    builder.CreateCall(printfFunc, {formatStr, argString});
}
