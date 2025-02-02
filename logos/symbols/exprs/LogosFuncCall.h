#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "LogosParser.h"
#include "LogosUnaryExpr.h"
#include "funcs/LogosFunc.h"
#include "exprs/LogosExpr.h"
#include "stmts/LogosStmt.h"

class LogosFuncCall final : public LogosStmt, public LogosUnaryExpr {
public:
    string name;
    vector<LogosExpr*> args;
    Position position = Position();

    explicit LogosFuncCall(const string& name) : name(name) {}
    Value* getLLVMValue(IRBuilder<>* builder, LogosStack* theStack, Module* module) override;
    ~LogosFuncCall() override;
    void setPosition(const antlr4::Token* ctx, const string& filePath) override;
};

#endif //LOGOSFUNCCALLEXPR_H
