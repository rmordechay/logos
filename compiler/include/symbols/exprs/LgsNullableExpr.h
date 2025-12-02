#pragma once
#include "LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    LgsExpr* baseExpr = nullptr;
    bool isNull = false;

    explicit LgsNullableExpr(LgsExpr* baseExpr): baseExpr(baseExpr) {}
    explicit LgsNullableExpr(const bool isNull): isNull(isNull) {}
    std::string asText() override;
    Value* loadIR(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    void hashNode(size_t& oldHash) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    Value* hashValue(LgsCgModule& cg) override;
    bool equals(LgsExpr* other) override;
};
