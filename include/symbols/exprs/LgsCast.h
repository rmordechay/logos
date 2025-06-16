#pragma once
#include "LgsExpr.h"
#include "LgsValue.h"

class LgsType;
class LgsExpr;

class LgsCast final : public LgsExpr {
public:
    LgsType* toType = nullptr;
    LgsExpr* fromValue = nullptr;
    LgsExpr* toValue = nullptr;

    LgsCast(LgsType* castToType, LgsExpr* castFromValue) : LgsExpr(castToType), toType(castToType), fromValue(castFromValue) {}
    Value* createIRValue(LgsRuntime* runtime) override;
    Value* addIR(LgsRuntime* runtime, LgsExpr* other) override;
    std::string pName() override;
    ~LgsCast() override;
};


