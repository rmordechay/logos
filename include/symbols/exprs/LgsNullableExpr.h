#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    static constexpr auto nullLiteral = "null";
    LgsExpr* baseExpr = nullptr;
    bool isNull = false;

    explicit LgsNullableExpr(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        isNull = !baseExpr;
        if (baseExpr) {
            if (baseExpr->type->asNullable()) {
                type = baseExpr->type;
            } else {
                type = new LgsNullable(baseExpr->type);
            }
        } else {
            type = new LgsNullable(nullptr);
        }
        isMutable = true;
    }
    std::string asText() override;
    void completeType(LgsType* toType) override;
    void store(LgsLLVMGen& cg, Value* value, const bool isSet) const;
    ~LgsNullableExpr() override;
};

