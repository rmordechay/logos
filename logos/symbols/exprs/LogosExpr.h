#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"
#include "../LogosStack.h"

class LogosExpr: public CodeGeneration {
public:
    const LogosType* type = nullptr;

    explicit LogosExpr(const LogosType* type) : type(type) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosExpr() override = default;
};

#endif //LOGOSEXPR_H

