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
    bool isConst = false;

    explicit LgsVarDec(const std::string& name, LgsExpr* expr) : name(name), expr(expr) {}
    llvm::Value* loadIR(LgsLLVM& codeGen) override;
    bool shouldAllocate(const llvm::Type* IRType) const;
    void setDebugValue(LgsLLVM& codeGen) override;
    json::value asJSON() override;
    ~LgsVarDec() override;
};


