#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec4 final : public LgsUnaryExpr {
public:
    LgsExpr* x;
    LgsExpr* y;
    LgsExpr* z;
    LgsExpr* w;

    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsVec4() override = default;
};


