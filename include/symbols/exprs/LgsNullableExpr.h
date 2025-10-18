#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    bool isNull = false;
    LgsExpr* baseExpr = nullptr;
    LgsNullable* nullableType = nullptr;

    explicit LgsNullableExpr(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        isNull = !baseExpr;
        if (baseExpr) {
            if (const auto n = baseExpr->type->asNullable()) {
                nullableType = n;
            } else {
                nullableType = new LgsNullable(baseExpr->type);
            }
        } else {
            nullableType = new LgsNullable(nullptr);
        }
        type = nullableType;
        isMutable = true;
    }
    std::string asText() override;
    void completeType(LgsType* toType) override;
    void assign(LgsLLVMGen& cg, LgsExpr* expr) override;
    ~LgsNullableExpr() override;
};

