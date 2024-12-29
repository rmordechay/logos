#include "StoreInt.h"
#include "types/LogosInt.h"

void StoreInt::generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const {
    const auto int32Ty = Type::getInt32Ty(context);
    const auto allocaInt = builder.CreateAlloca(int32Ty);
    const auto left = argsSymbols[0];
    const int intValue = std::dynamic_pointer_cast<LogosInt>(left->logosType)->value;
    builder.CreateStore(ConstantInt::get(int32Ty, intValue), allocaInt);
}
