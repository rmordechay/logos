#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    string composedName;
    vector<LgsExpr*> args;
    LgsFunc* func = nullptr;

    explicit LgsFuncCall(const string& name, const vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    string getName() override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void setComposedName();
    ~LgsFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H
