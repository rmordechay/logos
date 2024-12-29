#include "Print.h"

#include "types/LogosString.h"

#include <types/LogosInt.h>

void Print::generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const {
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::getUnqual(builder.getInt8Ty()), true);
    const auto printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", module);

    const auto param1 = argsSymbols[0];
    if (const auto logosStr = std::dynamic_pointer_cast<LogosString>(param1->logosType)) {
        auto formatStr = builder.CreateGlobalStringPtr("Printing: %s\n");
        const auto strValue = builder.CreateGlobalStringPtr(logosStr->value);
        builder.CreateCall(printfFunc, {formatStr, strValue});
    } else if (const auto logosInt = std::dynamic_pointer_cast<LogosInt>(param1->logosType)) {
        auto formatStr = builder.CreateGlobalStringPtr("Printing: %d\n");
        auto intValue = ConstantInt::get(builder.getInt32Ty(), logosInt->value);
        builder.CreateCall(printfFunc, {formatStr, intValue});
    } else {
        auto formatStr = builder.CreateGlobalStringPtr("Did not find any values\n");
        builder.CreateCall(printfFunc, {formatStr});
    }
}
