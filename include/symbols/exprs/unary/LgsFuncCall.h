#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    string parentName;
    vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    LgsSymbol* ref = nullptr;

    explicit LgsFuncCall(const string& name, const vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    string getName() override;
    string format(string& indentStr) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H
