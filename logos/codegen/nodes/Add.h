#ifndef ADD_H
#define ADD_H
#include "CodeNode.h"


class Add final : public CodeNode {
public:
    explicit Add(LogosSymbol* args...): CodeNode(args) {}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override;
};

#endif //ADD_H
