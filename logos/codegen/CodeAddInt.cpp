#include "codegen/CodeAddInt.h"

void CodeAddInt::generateCode(const LLVMContext& context, const IRBuilder<>& builder, Module* module) {
    std::cout << left.get() << std::endl;
    std::cout << right.get() << std::endl;
    std::cout << "CodeAdd::generateCode" << std::endl;
}
