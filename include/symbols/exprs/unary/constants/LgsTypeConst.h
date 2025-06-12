#pragma once
#include "types/LgsType.h"
#include <exprs/unary/LgsUnaryExpr.h>

class LgsTypeConst final : public LgsUnaryExpr {
public:
    explicit LgsTypeConst(LgsType* type) : LgsUnaryExpr(type) {
        type->isConst = true;
    }
    inline string getName() override;
    Value* createIRValue(LgsRuntime* runtime) override;
    ~LgsTypeConst() override = default;
};


