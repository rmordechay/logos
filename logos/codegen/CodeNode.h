#ifndef CODEGENNODE_H
#define CODEGENNODE_H
#include "LogosSymbol.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeNode {
public:
    std::vector<LogosSymbol *> args;

    explicit CodeNode() {}
    template <typename... Args>
    explicit CodeNode(Args&& ...args) : args({std::forward<Args>(args)...}) {}

    virtual void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const = 0;
    virtual ~CodeNode() = default;
};

#endif //CODEGENNODE_H
