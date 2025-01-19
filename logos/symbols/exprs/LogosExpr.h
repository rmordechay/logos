#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"
#include "StackFrame.h"

class LogosExpr: public CodeGeneration {
public:
    const LogosType* type = nullptr;

    explicit LogosExpr(const LogosType* type) : type(type) {}
    Value* getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) override;
    ~LogosExpr() override = default;
};

#endif //LOGOSEXPR_H

