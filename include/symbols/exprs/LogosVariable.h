#ifndef LOGOSVARIABLEEXPR_H
#define LOGOSVARIABLEEXPR_H
#include "LogosUnaryExpr.h"
#include "stmts/LogosVarDec.h"

class LogosVariable final :  public LogosUnaryExpr {
public:
    std::string name;

    explicit LogosVariable(const std::string& name, LogosType* variableType) : LogosUnaryExpr(variableType), name(name) {}
    explicit LogosVariable(const std::string& name) : LogosVariable(name, nullptr) {}
    string getName() override;
    LogosSymbolType getSymbolType() override;
    Value* getLLVMValue(CodeGenMetadata* metadata) override;
    ~LogosVariable() override = default;
};

#endif //LOGOSVARIABLEEXPR_H
