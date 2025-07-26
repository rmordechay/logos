#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsLong.h"

class LgsLongConst final : public LgsUnaryExpr {
public:
    long value;

    explicit LgsLongConst(const int value) : LgsUnaryExpr(&LGS_LONG), value(value) {}
    string prettyName() override;
    Value* createIRValue(LgsModule* module) override;
    ~LgsLongConst() override = default;
};




