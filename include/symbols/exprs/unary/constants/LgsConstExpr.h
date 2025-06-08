#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsType.h"


class LgsFloatConst;
class LgsBool;
class LgsIntConst;
class LgsStrConst;


class LgsConstExpr : public LgsUnaryExpr {
public:
    explicit LgsConstExpr(LgsType* type) : LgsUnaryExpr(type) {
        type->isConst = true;
    }
    ~LgsConstExpr() override = default;
};


