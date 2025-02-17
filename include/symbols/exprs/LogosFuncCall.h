#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "LogosParser.h"
#include "LogosUnaryExpr.h"
#include "stmts/LogosStmt.h"

class LogosFuncCall final : public LogosStmt, public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    Position position = Position();

    explicit LogosFuncCall(const string& name) : name(name) {}
    string getName() override;
    Value* computeIRValue(CodeGenMetadata* metadata) override;
    LogosSymbolType getSymbolType() override;
    ~LogosFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H
