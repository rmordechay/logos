#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    static constexpr auto nullLiteral = "null";
    LgsExpr* baseExpr = nullptr;
    bool isNull = false;

    LgsNullableExpr() {
        type = new LgsNullable(nullptr);
        isNull = true;
    }
    explicit LgsNullableExpr(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = new LgsNullable(baseExpr->type);
    }
    json::value asJsonStr() override;
    std::string getName() override;
    void completeType(LgsType* toType) override;
    void storeValue(LgsLLVMGen& cg, Value* value, const bool null) const;
    ~LgsNullableExpr() override;
};

