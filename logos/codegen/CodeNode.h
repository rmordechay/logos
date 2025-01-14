#ifndef CODENODE_H
#define CODENODE_H
#include "RuntimeScope.h"

#include <llvm/IR/IRBuilder.h>

class CodeNode {
public:
    LLVMContext *context = nullptr;
    IRBuilder<> *builder = nullptr;
    Module *module = nullptr;

    virtual void generateProlog(RuntimeScope* scope) = 0;
    virtual void generateEpilog(RuntimeScope* scope) = 0;
    virtual ~CodeNode() = default
    ;
};

#endif //CODENODE_H
