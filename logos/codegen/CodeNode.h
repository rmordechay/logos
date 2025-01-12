#ifndef CODENODE_H
#define CODENODE_H

#include <map>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>

using namespace llvm;

class CodeNode {
public:
    virtual ~CodeNode() = default;
    virtual void generateCode(IRBuilder<>& builder, Module* module, std::map<std::string, Function*> functions) = 0;
};

#endif //CODENODE_H
