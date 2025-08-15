#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

class LgsVarDec final : public LgsStmt {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isNullable = false;

    explicit LgsVarDec(const std::string& name, LgsExpr* expr) : name(name), expr(expr) {
        type = expr->type;
    }
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string format(std::string& indentStr) override;
    bool shouldAllocate(const Type* IRType) const;
    ~LgsVarDec() override;
};


