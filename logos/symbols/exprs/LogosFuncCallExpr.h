#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "StackFrame.h"
#include "funcs/LogosFunc.h"
#include "exprs/LogosExpr.h"
#include "exprs/LogosUnaryExpr.h"
#include <map>

class LogosFuncCallExpr final : public LogosStmt, public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;

    explicit LogosFuncCallExpr(const string& name) : name(name) {}
    explicit LogosFuncCallExpr(const LogosType* type, const vector<LogosExpr*>& args) :
        LogosUnaryExpr(type), args(args) {}

    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame, Module* module) override;
    ~LogosFuncCallExpr() override;
};

#endif //LOGOSFUNCCALLEXPR_H
