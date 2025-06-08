#pragma once
#include "LgsConstExpr.h"

#include <exprs/unary/LgsUnaryExpr.h>

class LgsTypeConst : public LgsConstExpr {
public:
    explicit LgsTypeConst(LgsType* type) : LgsConstExpr(type) {}
    inline string getName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsTypeConst() override = default;
};


