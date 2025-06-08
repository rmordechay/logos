#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec3 final : public LgsUnaryExpr {
public:
    LgsExpr* x;
    LgsExpr* y;
    LgsExpr* z;

    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsVec3() override = default;
};


