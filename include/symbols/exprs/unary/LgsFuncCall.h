#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    LgsSymbol* ref = nullptr;
    bool isMethodCall;

    explicit LgsFuncCall(const string& name, const bool isMethodCall, const vector<LgsExpr*>& args = {}) : name(name), args(args), isMethodCall(isMethodCall) {}
    string getName() override;
    string format(string& indentStr) override;
    string getSignatureText(bool withType = false) const;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    void free(CodeGenMetadata* metadata) override;
    ~LgsFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H
