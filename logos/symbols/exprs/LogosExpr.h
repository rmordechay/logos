#ifndef LOGOSEXPR_H
#define LOGOSEXPR_H
#include "CodeGeneration.h"
#include "StackFrame.h"

class LogosExpr: public CodeGeneration {
public:
    const LogosType& type;

    explicit LogosExpr(const LogosType& type) : type(type) {}
    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    ~LogosExpr() override = default;
};

#endif //LOGOSEXPR_H

