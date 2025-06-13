#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsVarDec final : public LgsStmt {
public:
    string name;
    LgsType* type = nullptr;
    bool isConst = false;
    LgsExpr* expr = nullptr;
    vector<LgsVariable*> refs;

    explicit LgsVarDec(const string& name, LgsExpr* expr = nullptr) : name(name), expr(expr) {}
    void createIRStmt(LgsRuntime* runtime) override;
    string format(string& indentStr) override;
    bool shouldAllocate(const Type* IRType) const;
    ~LgsVarDec() override;
};


