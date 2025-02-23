#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosUnaryExpr.h"
#include "stmts/LogosVarDec.h"

class LogosVariable final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariable(const std::string& name) : LogosUnaryExpr(nullptr), name(name) {}
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    LogosSymbolType getSymbolType() override;
    void setName(string name) override;
    string getName() override;
    ~LogosVariable() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
