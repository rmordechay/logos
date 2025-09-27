#pragma once
#include "exprs/LgsExpr.h"
#include "LgsValue.h"


class LgsType;
class LgsExpr;

class LgsCast final : public LgsExpr {
public:
    LgsType* toType = nullptr;
    LgsExpr* fromValue = nullptr;
    LgsExpr* toValue = nullptr;

    LgsCast(LgsType* castToType, LgsExpr* castFromValue) : LgsExpr(castToType), toType(castToType), fromValue(castFromValue) {}
    std::string pname() override;
    json::value asJsonStr() override;
    ~LgsCast() override;
};


