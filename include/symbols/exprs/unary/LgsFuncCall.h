#ifndef LOGOSFUNCCALLEXPR_H
#define LOGOSFUNCCALLEXPR_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    LgsFuncType* funcType = nullptr;
    LgsSymbol* ref = nullptr;
    bool isMethodCall;

    explicit LgsFuncCall(const string& name, const bool isMethodCall, const vector<LgsExpr*>& args = {}) : name(name), args(args), isMethodCall(isMethodCall) {}
    string getName() override;
    string format(string& indentStr) override;
    string getSignatureText(bool withType = false) const;
    void createIRStmt(CodeGenMetadata* metadata) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    Value* call(CodeGenMetadata* metadata, const vector<LgsExpr*>& args) const;
    ~LgsFuncCall() override;
};

#endif //LOGOSFUNCCALLEXPR_H
