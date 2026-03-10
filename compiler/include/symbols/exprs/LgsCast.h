#pragma once
#include <string>

#include "exprs/LgsExpr.h"

class LgsType;
class LgsExpr;

class LgsCast final : public LgsExpr {
public:
    LgsExpr* fromValue = nullptr;
    LgsType* toType = nullptr;
    LgsExpr* value = nullptr;

    LgsCast(LgsExpr* fromValue, LgsType* toType) : fromValue(fromValue), toType(toType) {}
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsCast() override;
};


