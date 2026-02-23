#pragma once
#include <cmath>
#include <string>

#include "exprs/LgsExpr.h"

class LgsType;

class LgsFloatConst final : public LgsExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsExpr(type), value(value) {
        isMutable = false;
    }
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    LgsExpr* clone() override;
    ~LgsFloatConst() override = default;
};
