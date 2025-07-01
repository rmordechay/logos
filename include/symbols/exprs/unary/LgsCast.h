#pragma once
#include "exprs/LgsExpr.h"
#include "LgsValue.h"
#include "LgsUnaryExpr.h"

class LgsType;
class LgsExpr;

class LgsCast final : public LgsUnaryExpr {
public:
    LgsType* toType = nullptr;
    LgsExpr* fromValue = nullptr;
    LgsExpr* toValue = nullptr;

    LgsCast(LgsType* castToType, LgsExpr* castFromValue) : LgsUnaryExpr(castToType), toType(castToType), fromValue(castFromValue) {}
    Value* createIRValue(LgsModule* runtime) override;
    Value* addIR(LgsModule* runtime, LgsExpr* other) override;
    std::string prettyName() override;
    ~LgsCast() override;
};


