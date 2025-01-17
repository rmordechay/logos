#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "exprs/LogosExpr.h"

class LogosVarDefinition final : public CodeGeneration {
public:
    string name;
    LogosExpr* expr;


    explicit LogosVarDefinition(const string& name, LogosExpr* expr) : name(name), expr(expr) {}
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    const LogosType& getType() const override;
    ~LogosVarDefinition() override = default;
};



#endif //LOGOSVARDEFINITION_H
