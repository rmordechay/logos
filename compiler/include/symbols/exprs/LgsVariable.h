#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"
struct LgsSymbol;

class LgsVariable final : public LgsExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsExpr(type), name(name) {}
    Value* loadIR(LgsCodeGen& cg) override;
    bool equals(LgsExpr* other) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void assign(LgsCodeGen& cg, LgsExpr* right) override;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsVariable* clone() override;
};