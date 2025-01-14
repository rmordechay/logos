#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosSymbol.h"

class LogosVariableExpr final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariableExpr(const LogosType& variableType, const std::string& name) : LogosUnaryExpr(variableType), name(name) {}
    ~LogosVariableExpr() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
