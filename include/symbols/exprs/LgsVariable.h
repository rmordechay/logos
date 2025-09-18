#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"
struct LgsSymbol;

class LgsVariable final : public LgsExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsExpr(type), name(name) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    Value* hash(LgsLLVMGen& cg) override;
    LgsExpr* castTo(LgsType* toType) override;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    std::string pname() override;
    json::value asJSON() override;
};