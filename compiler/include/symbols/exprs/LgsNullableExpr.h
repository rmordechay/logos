#pragma once
#include "LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNullableExpr final : public LgsExpr {
public:
    LgsExpr* baseExpr = nullptr;

    explicit LgsNullableExpr(LgsExpr* baseExpr): baseExpr(baseExpr) {}
    LgsNullableExpr(): LgsExpr(&LGS_NULLABLE) {
        isNull = true;
    }
    Value* loadIR(LgsCgModule& cg) override;
    void assign(LgsCgModule& cg, LgsExpr* expr, Value* level) override;
    void setDebugValue(LgsCgModule& cg) override;
    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
};
