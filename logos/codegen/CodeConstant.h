#ifndef CODECONSTANT_H
#define CODECONSTANT_H
#include "LogosCodeNode.h"


class CodeConstant final : public LogosCodeNode  {
public:
    void generateCode(const LLVMContext& context, const IRBuilder<>& builder, Module* module) override;
};



#endif //CODECONSTANT_H
