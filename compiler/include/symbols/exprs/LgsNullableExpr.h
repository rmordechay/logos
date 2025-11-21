#pragma once
#include "LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    LgsExpr* baseExpr;
    LgsNullable* nullableType;

    explicit LgsNullableExpr(LgsExpr* baseExpr): baseExpr(baseExpr) {
        nullableType = new LgsNullable(nullptr);
        type = nullableType;
    }
    std::string asText() override;
    Value* loadIR(LgsLLVMGen& cg) override;
    void setDebugValue(LgsLLVMGen& cg) override;
    void hashNode(size_t& oldHash) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* hashValue(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    LgsExpr* clone() override;
};
