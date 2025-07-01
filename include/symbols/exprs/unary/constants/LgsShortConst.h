#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsShort.h"

class LgsShortConst final : public LgsUnaryExpr {
public:
    int value;

    explicit LgsShortConst(const int value) : LgsUnaryExpr(&LGS_SHORT), value(value) {}
    string prettyName() override;
    Value* createIRValue(LgsModule* runtime) override;
    LgsExpr* convertExpr(LgsType* toType) override;
    LgsExpr* clone() override;
    ~LgsShortConst() override = default;
};



