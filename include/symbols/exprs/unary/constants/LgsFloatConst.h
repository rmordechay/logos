#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsFloat.h"

class LgsFloatConst final : public LgsUnaryExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsUnaryExpr(type), value(value) {
        isConstant = true;
    }
    void createIRValue(LgsCodeGen* codeGen) override;
    json::object asJSON() override;
    std::string pname() override;
    ~LgsFloatConst() override = default;
};
