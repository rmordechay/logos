#pragma once
#include "exprs/LgsExpr.h"
#include <cmath>

class LgsFloatConst final : public LgsExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsExpr(type), value(value) {
        isMutable = false;
    }
    Value* loadIR(LgsCgModule& cg) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    Value* castIR(LgsCgModule& cg, LgsType* toType) override;
    std::string asText() override;
    ~LgsFloatConst() override = default;
};
