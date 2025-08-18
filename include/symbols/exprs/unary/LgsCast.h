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
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    Value* addIR(LgsCodeGen* codeGen, LgsExpr* other) override;
    std::string pname() override;
    ~LgsCast() override;
};


