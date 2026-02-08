#pragma once
#include "LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    LgsExpr* baseExpr = nullptr;

    explicit LgsNullableExpr(LgsExpr* baseExpr): baseExpr(baseExpr) {}
    LgsNullableExpr(): LgsExpr(new LgsNullable()) {
        isNull = true;
    }
    Value* loadIR(LgsCodeGen& cg) override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* cast(bool explicitly) override;
    std::string asText() override;
    LgsExpr* clone() override;
};
