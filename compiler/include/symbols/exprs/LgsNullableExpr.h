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
    Value* loadIR(LgsCodeGen& cg) override;
    void assign(LgsCodeGen& cg, LgsExpr* right) override;
    void setDebugValue(LgsCodeGen& cg) override;
    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
};
