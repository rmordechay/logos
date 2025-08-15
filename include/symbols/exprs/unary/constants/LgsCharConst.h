#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsChar.h"

class LgsCharConst final : public LgsUnaryExpr {
public:
    char value;
    explicit LgsCharConst(const char value) : LgsUnaryExpr(&LGS_CHAR), value(value) {}
    std::string prettyName() override;
    void createIRValue(LgsCodeGen* codeGen) override;
};


