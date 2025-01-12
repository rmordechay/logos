#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosSymbol.h"
#include "LogosUnaryExpr.h"

class LogosVariableExpr final : public LogosUnaryExpr {
public:
    std::string name;
    LogosSymbol symbol;

    explicit LogosVariableExpr(const std::string& name, const LogosSymbol& symbol) : LogosUnaryExpr(nullptr), name(name), symbol(symbol) {}
};

#endif //LOGOSVARIABLEEXPR_H
