#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsFloat.h"

class LgsFloatConst final : public LgsUnaryExpr {
public:
    double value;

    explicit LgsFloatConst(const float value) : LgsUnaryExpr(&LGS_FLOAT), value(value) {}
    Value* createIRValue(LgsCodeGen* codeGen) override;
    std::string prettyName() override;
    ~LgsFloatConst() override = default;
};


