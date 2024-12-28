#ifndef BUILTINFUNC_H
#define BUILTINFUNC_H
#include "CodeNode.h"
#include "LogosSymbol.h"

class BuiltinFunc : public CodeNode {
public:
    explicit BuiltinFunc() {}
    explicit BuiltinFunc(LogosSymbol* args...): CodeNode(args) {}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override = 0;
};


#endif //BUILTINFUNC_H
