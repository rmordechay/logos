#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosSymbol.h"
#include "LogosUnaryExpr.h"
#include "StackFrame.h"

class LogosVariableExpr final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariableExpr(const LogosType& variableType, const std::string& name) : LogosUnaryExpr(variableType), name(name) {}
    const LogosType& getType() const override;
    Value* getLLVMValue(IRBuilder<>* builder, RuntimeStackFrame* stackFrame) override;
    ~LogosVariableExpr() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
