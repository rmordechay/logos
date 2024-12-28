#ifndef CODEGENNODE_H
#define CODEGENNODE_H
#include "LogosSymbol.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeNode {
public:
    std::vector<LogosSymbol *> args;

    virtual void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const = 0;

protected:
    explicit CodeNode() {}
    template <typename... Args>
    explicit CodeNode(Args&& ...args) : args({std::forward<Args>(args)...}) {}
    virtual ~CodeNode() = default;
};

#endif //CODEGENNODE_H
