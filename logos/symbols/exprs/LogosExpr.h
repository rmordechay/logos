#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"

class LogosExpr: public CodeGeneration {
public:
    LogosType* type = nullptr;

    explicit LogosExpr(LogosType* type) : type(type) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) override;
    ~LogosExpr() override = default;
};

#endif //LOGOSEXPR_H

