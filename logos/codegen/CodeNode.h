#ifndef CODEGENNODE_H
#define CODEGENNODE_H
#include "LogosSymbol.h"
#include <llvm/IR/Type.h>
#include <iostream>
#include <ostream>
#include <llvm/IR/IRBuilder.h>

using namespace llvm;

class CodeNode {
public:
    LogosSymbol *left;
    LogosSymbol *right;
    virtual ~CodeNode() = default;
    virtual void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const = 0;

protected:
    explicit CodeNode(LogosSymbol *left, LogosSymbol *right): left(left), right(right) {}
};

class StoreInt final : public CodeNode {
public:
    explicit StoreInt(LogosSymbol *left): CodeNode(left, nullptr) {}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override;
};

class Add final : public CodeNode {
public:
    explicit Add(LogosSymbol *left, LogosSymbol *right): CodeNode(left, right){}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override;
};

class FuncCall final : public CodeNode {
public:
    explicit FuncCall(LogosSymbol *left): CodeNode(left, nullptr) {}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override;
};

#endif //CODEGENNODE_H
