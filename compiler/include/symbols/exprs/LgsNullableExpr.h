#pragma once
#include "LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsNullable* nullableType;

    explicit LgsNullableExpr(LgsExpr* baseExpr): baseExpr(baseExpr) {
        nullableType = new LgsNullable(nullptr);
        setType(nullableType);
    }
    std::string asText() override;
    Value* loadIR(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    void hashNode(size_t& oldHash) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    Value* hashValue(LgsCgModule& cg) override;
    bool equals(LgsExpr* other) override;
};
