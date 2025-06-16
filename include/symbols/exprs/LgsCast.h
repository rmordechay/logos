#pragma once
#include "LgsExpr.h"
#include "LgsValue.h"
#include "unary/LgsUnaryExpr.h"

class LgsType;
class LgsExpr;

class LgsCast final : public LgsUnaryExpr {
public:
    LgsType* toType = nullptr;
    LgsExpr* fromValue = nullptr;
    LgsExpr* toValue = nullptr;

    LgsCast(LgsType* castToType, LgsExpr* castFromValue) : LgsUnaryExpr(castToType), toType(castToType), fromValue(castFromValue) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    std::string pName() override;
    ~LgsCast() override;
};


