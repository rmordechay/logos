#pragma once
#include "stmts/LgsStmt.h"
#include "LgsUnaryExpr.h"

class LgsFuncType;
struct LgsSymbol;

class LgsFuncCall final : public LgsStmt, public LgsUnaryExpr {
public:
    string name;
    vector<LgsExpr*> args;
    LgsSymbol* callback = nullptr;
    LgsFunc* func = nullptr;

    explicit LgsFuncCall(const string& name, const vector<LgsExpr*>& args = {}) : name(name), args(args) {}
    void resolveVirtualFunc(LgsModule* runtime) const;
    Value* call(LgsModule* runtime) const;
    Value* getCallback(LgsModule* runtime) const;
    bool equals(const LgsFuncType* other) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaultParams(const LgsFuncType* funcType) const;
    void createIRStmt(LgsModule* runtime) override;
    Value* createIRValue(LgsModule* runtime) override;
    string getExprName() override;
    string format(string& indentStr) override;
    string prettyName() override;
    ~LgsFuncCall() override = default;
};
