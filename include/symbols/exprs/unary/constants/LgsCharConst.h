#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsChar.h"

class LgsCharConst final : public LgsUnaryExpr {
public:
    char value;
    explicit LgsCharConst(const char value) : LgsUnaryExpr(&LGS_CHAR), value(value) {
        type->setFlag(CONST);
    }
    Value* createIRValue(LgsRuntime* runtime) override;
};


