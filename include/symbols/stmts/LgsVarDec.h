#pragma once
#include "LgsStmt.h"
#include "exprs/LgsExpr.h"

namespace llvm {
    class Type;
}

class LgsVarDec final : public LgsStmt {
public:
    std::string name;
    LgsType* type = nullptr;
    LgsExpr* expr = nullptr;
    bool isNullable = false;

    explicit LgsVarDec(const std::string& name, LgsExpr* expr) : name(name), expr(expr) {}
    bool shouldAllocate(const llvm::Type* IRType) const;
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    ~LgsVarDec() override;
};


