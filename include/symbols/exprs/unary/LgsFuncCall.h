#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "stmts/LgsStmt.h"
#include "LogosUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    vector<LgsExpr*> args;
    Location position = Location();

    explicit LgsFuncCall(const string& name) : name(name) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    ~LgsFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H
