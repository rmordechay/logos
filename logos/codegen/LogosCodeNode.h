#ifndef LOGOSCODENODE_H
#define LOGOSCODENODE_H
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class LogosCodeNode {
public:
    virtual ~LogosCodeNode() = default;
    virtual void generateCode(const LLVMContext& context, const IRBuilder<>& builder, Module* module) = 0;
};

#endif //LOGOSCODENODE_H
