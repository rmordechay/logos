#ifndef LOGOSVARDEFINITION_H
#define LOGOSVARDEFINITION_H
#include "LogosStack.h"
#include "LogosStmt.h"
#include "exprs/LogosExpr.h"

class LogosVarDec final : public LogosStmt {
public:
    string name;
    const LogosType* type;
    LogosExpr* expr;

    explicit LogosVarDec(const string& name, LogosExpr* expr) : name(name), type(expr->type), expr(expr) {}
    explicit LogosVarDec(const string& name, const LogosType* type) : name(name), type(type), expr(nullptr) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosVarDec() override;
};



#endif //LOGOSVARDEFINITION_H
