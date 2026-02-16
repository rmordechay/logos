#pragma once
#include "exprs/LgsExpr.h"
#include <cmath>

class LgsFloatConst final : public LgsExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsExpr(type), value(value) {}
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* clone() override;
    ~LgsFloatConst() override = default;
};
