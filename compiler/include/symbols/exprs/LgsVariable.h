#pragma once
#include "LgsSymbol.h"
#include "exprs/LgsExpr.h"
struct LgsSymbol;

class LgsVariable final : public LgsExpr {
public:
    std::string name;
    LgsSymbol ref;

    explicit LgsVariable(const std::string& name, LgsType* type = nullptr) : LgsExpr(type), name(name) {}
    bool equals(LgsExpr* other) override;
    LgsExpr* cast(LgsType* toType, bool explicitly) override;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsVariable* clone() override;
};