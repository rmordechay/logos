#include "CodeNode.h"

void StoreInt::generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const {
    const auto int32Ty = Type::getInt32Ty(context);
    const auto allocaInt = builder.CreateAlloca(int32Ty);
    const int intValue = *left->logosValue->value.intValue;
    builder.CreateStore(ConstantInt::get(int32Ty, intValue), allocaInt);
}

void Add::generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const {
    std::cout << "Add " << std::endl;
}


void FuncCall::generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const {
    const auto argStr = *left->logosValue->value.stringValue;
    const auto argString = builder.CreateGlobalStringPtr(argStr);
    const auto printfType = FunctionType::get(builder.getInt32Ty(), PointerType::getUnqual(builder.getInt8Ty()), true);
    const auto printfFunc = Function::Create(printfType, Function::ExternalLinkage, "printf", module);
    auto formatStr = builder.CreateGlobalStringPtr("%s\n", "name");
    builder.CreateCall(printfFunc, {formatStr, argString});
}
