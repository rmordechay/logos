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
    Value* call(LgsModule* module) const;
    Value* getCallback(LgsModule* module) const;
    void createIRStmt(LgsModule* module) override;
    Value* createIRValue(LgsModule* module) override;
    bool equals(const LgsFuncType* funcType) const;
    bool equalsVariadic(const LgsFuncType* funcType) const;
    bool equalsDefaultParams(const LgsFuncType* funcType) const;
    void resolveVirtualFunc(LgsModule* module) const;
    string format(string& indentStr) override;
    string prettyName() override;
    ~LgsFuncCall() override = default;
};
