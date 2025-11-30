#pragma once
#include "exprs/LgsExpr.h"

class LgsType;
class LgsExpr;

class LgsCast final : public LgsExpr {
public:
    LgsExpr* fromValue = nullptr;
    LgsType* toType = nullptr;
    LgsExpr* value = nullptr;

    LgsCast(LgsExpr* fromValue, LgsType* toType) : fromValue(fromValue), toType(toType) {}
    Value* loadIR(LgsCgModule& cg) override;
    std::string asText() override;
    ~LgsCast() override;
};


