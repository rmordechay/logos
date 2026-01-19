#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"
struct LgsSymbol;

class LgsVariable final : public LgsExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsExpr(type), name(name) {}
    Value* loadIR(LgsCgModule& cg) override;
    bool equals(LgsExpr* other) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    Value* hashValue(LgsCgModule& cg) override;
    void assign(LgsCgModule& cg, LgsExpr* right) override;
    std::string asText() override;
    void setDebugValue(LgsCgModule& cg) override;
    LgsVariable* clone() override;
};