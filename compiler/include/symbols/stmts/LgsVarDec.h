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
    LgsVarDec(const std::string& name, LgsType* type, LgsExpr* expr) : name(name), type(type), expr(expr) {}
    void setType(LgsType* newType);
    Value* loadIR(LgsCgModule& cg) override;
    bool shouldAllocate() const;
    void setDebugValue(LgsCgModule& cg) override;
    void hashNode(size_t& oldHash) override;
    ~LgsVarDec() override;
};


