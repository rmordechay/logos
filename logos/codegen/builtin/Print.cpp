#include "Print.h"

#include "types/LogosString.h"

#include <types/LogosInt.h>

void Print::generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const {
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::getUnqual(builder.getInt8Ty()), true);
    const auto printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", module);

    const auto left = args[0];
    if (const auto logosStr = dynamic_cast<LogosString*>(left->logosType)) {
        auto formatStr = builder.CreateGlobalStringPtr("Printing: %s\n");
        const auto strValue = builder.CreateGlobalStringPtr(logosStr->value);
        builder.CreateCall(printfFunc, {formatStr, strValue});
    }

    if (const auto logosInt = dynamic_cast<LogosInt*>(left->logosType)) {
        auto formatStr = builder.CreateGlobalStringPtr("Printing: %d\n");
        auto intValue = ConstantInt::get(builder.getInt32Ty(), logosInt->value);
        builder.CreateCall(printfFunc, {formatStr, intValue});
    }
}
