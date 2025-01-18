#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "exprs/LogosExpr.h"

class LogosVarDec final : public CodeGeneration {
public:
    string name;
    LogosExpr* expr;

    explicit LogosVarDec(const string& name, LogosExpr* expr) : name(name), expr(expr) {}
    explicit LogosVarDec(const string& name) : LogosVarDec(name, nullptr) {}
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    const LogosType& getType() const override;
    ~LogosVarDec() override = default;
};



#endif //LOGOSVARDEFINITION_H
