#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsLong.h"

class LgsLongConst final : public LgsUnaryExpr {
public:
    long value;

    explicit LgsLongConst(const int value) : LgsUnaryExpr(&LGS_LONG), value(value) {}
    std::string prettyName() override;
    void createIRValue(LgsCodeGen* codeGen) override;
    ~LgsLongConst() override = default;
};




