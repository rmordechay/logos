#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosUnaryExpr.h"
#include "stmts/LogosVarDec.h"

class LogosVariable final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariable(const std::string& name, LogosType* variableType) : LogosUnaryExpr(variableType), name(name) {}
    explicit LogosVariable(const std::string& name) : LogosVariable(name, nullptr) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    LogosSymbolType getSymbolType() override;
    string getName() override;
    ~LogosVariable() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
