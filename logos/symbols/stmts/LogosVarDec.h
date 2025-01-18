#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "exprs/LogosExpr.h"

class LogosVarDec final : public CodeGeneration {
public:
    string name;
    const LogosType& type;
    LogosExpr* expr;

    explicit LogosVarDec(const string& name, LogosExpr* expr) : name(name), type(expr->getType()), expr(expr) {}
    explicit LogosVarDec(const string& name, const LogosType& type) : name(name), type(type), expr(nullptr) {}
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    const LogosType& getType() const override;
    ~LogosVarDec() override = default;
};



#endif //LOGOSVARDEFINITION_H
