#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsFloat.h"

class LgsFloatConst final : public LgsUnaryExpr {
public:
    float_t value;

    explicit LgsFloatConst(const float value) : LgsUnaryExpr(&LGS_FLOAT), value(value) {}
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string pname() override;
    ~LgsFloatConst() override = default;
};


