#ifndef LOGOSFUNCCALL_H
#define LOGOSFUNCCALL_H
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    vector<LgsExpr*> args;
    LgsSymbol* callback = nullptr;
    LgsFunc* func = nullptr;

    explicit LgsFuncCall(const string& name, const vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    Value* call(CodeGenMetadata* metadata) const;
    Value* getCallback(CodeGenMetadata* metadata) const;
    bool equalsRaw(const LgsFuncType* funcType) const;
    bool equals(const LgsFuncType* funcType) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaultParams(const LgsFuncType* funcType) const;
    Value* resolveVirtualFunc(CodeGenMetadata* metadata) const;
    void createIRStmt(CodeGenMetadata* metadata) override;
    Value* createIRValue(CodeGenMetadata* metadata) override;
    string getName() override;
    string format(string& indentStr) override;
    string prettyName() override;
    ~LgsFuncCall() override = default;
};

#endif //LOGOSFUNCCALL_H