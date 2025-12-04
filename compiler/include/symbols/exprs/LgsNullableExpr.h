#pragma once
#include "LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    LgsExpr* baseExpr = nullptr;

    LgsNullableExpr(): LgsExpr(new LgsNullable(nullptr)) {
        isNull = true;
    }
    explicit LgsNullableExpr(LgsExpr* baseExpr): baseExpr(baseExpr) {}
    Value* loadIR(LgsCgModule& cg) override;
    void setDebugValue(LgsCgModule& cg) override;
    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
};
