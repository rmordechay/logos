#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsVarDec final : public LgsStmt {
public:
    string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isNullable = false;

    explicit LgsVarDec(const string& name) : name(name) {}
    explicit LgsVarDec(const string& name, LgsExpr* expr) : name(name), expr(expr) {
        type = expr->type;
    }
    void createIRStmt(LgsCodeGen* codeGen) override;
    string format(string& indentStr) override;
    bool shouldAllocate(const Type* IRType) const;
    ~LgsVarDec() override;
};


