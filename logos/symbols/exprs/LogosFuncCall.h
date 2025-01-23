#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "../LogosStack.h"
#include "funcs/LogosFunc.h"
#include "exprs/LogosExpr.h"
#include "exprs/LogosUnaryExpr.h"
#include <map>

class LogosFuncCall final : public LogosStmt, public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;

    explicit LogosFuncCall(const string& name) : name(name) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* stackFrame, Module* module) override;
    ~LogosFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H
