#ifndef STOREINT_H
#define STOREINT_H
#include "CodeNode.h"

class StoreInt final : public CodeNode {
public:
    explicit StoreInt(LogosSymbol* args...): CodeNode(args) {}
    void generateCode(LLVMContext& context, IRBuilder<>& builder, Module* module) const override;
};

#endif //STOREINT_H
