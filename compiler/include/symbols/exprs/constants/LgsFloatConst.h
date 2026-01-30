#pragma once
#include "exprs/LgsExpr.h"
#include <cmath>

class LgsFloatConst final : public LgsExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsCodeGen& cg) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsFloatConst() override = default;
};
