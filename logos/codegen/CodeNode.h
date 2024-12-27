#ifndef CODEGENNODE_H
#define CODEGENNODE_H
#include "LogosSymbol.h"

#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeNode {
public:
    LogosSymbol *left;
    LogosSymbol *right;

    explicit CodeNode(LogosSymbol *left, LogosSymbol *right): left(left), right(right) {}
    virtual void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const = 0;
    virtual ~CodeNode() = default;
};

#endif //CODEGENNODE_H
