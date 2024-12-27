#ifndef BUILTINFUNC_H
#define BUILTINFUNC_H
#include "CodeNode.h"
#include "LogosSymbol.h"

class BuiltinFunc : public CodeNode {
public:
    BuiltinFunc(LogosSymbol* left, LogosSymbol* right) : CodeNode(left, right) {}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override = 0;
};


#endif //BUILTINFUNC_H
