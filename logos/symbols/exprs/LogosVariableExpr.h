#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosSymbol.h"
#include "LogosUnaryExpr.h"
#include "StackFrame.h"

class LogosVariableExpr final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariableExpr(const std::string& name) : LogosUnaryExpr(nullptr), name(name) {}
    explicit LogosVariableExpr(const LogosType* variableType, const std::string& name) : LogosUnaryExpr(variableType), name(name) {}
    Value* getLLVMValue(IRBuilder<>* builder, stack<LogosStackFrame>* stackFrame, Module* module) override;
    ~LogosVariableExpr() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
