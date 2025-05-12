#ifndef LOGOSFUNCCALL_H
#define LOGOSFUNCCALL_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    vector<LgsExpr*> args;
    LgsFunc* func = nullptr;
    LgsSymbol* ref = nullptr;

    explicit LgsFuncCall(const string& name, const vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    string getAsStr() const;
    Value* call(CodeGenMetadata* metadata) const;
    Value* resolveVirtualFunc(CodeGenMetadata* metadata) const;
    string getName() override;
    string format(string& indentStr) override;
    void createIRStmt(CodeGenMetadata* metadata) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsFuncCall() override;
};

#endif //LOGOSFUNCCALL_H
