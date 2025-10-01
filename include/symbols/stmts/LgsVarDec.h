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
    bool isOwner = false;

    explicit LgsVarDec(const std::string& name, LgsExpr* expr) : name(name), expr(expr) {}
    std::string getName() override;
    Value* loadIR(LgsLLVMGen& cg) override;
    void setDebugValue(LgsLLVMGen& cg) override;
    json::value asJsonStr() override;
    ~LgsVarDec() override;
};


