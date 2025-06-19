#pragma once
#include "LgsType.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsTypeConst final : public LgsUnaryExpr {
public:
    explicit LgsTypeConst(LgsType* type) : LgsUnaryExpr(type) {}
    string getExprName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsTypeConst() override = default;
};
