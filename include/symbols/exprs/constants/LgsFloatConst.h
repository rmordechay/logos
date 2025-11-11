#pragma once
#include "exprs/LgsExpr.h"
#include <cmath>

class LgsFloatConst final : public LgsExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsExpr(type), value(value) {
        isValueKnown = true;
    }
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
    ~LgsFloatConst() override = default;
};
