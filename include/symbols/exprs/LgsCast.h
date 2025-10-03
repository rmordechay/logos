#pragma once
#include "exprs/LgsExpr.h"

class LgsType;
class LgsExpr;

class LgsCast final : public LgsExpr {
public:
    LgsExpr* fromValue = nullptr;
    LgsType* toType = nullptr;
    LgsExpr* value = nullptr;

    LgsCast(LgsType* castToType, LgsExpr* castFromValue) : LgsExpr(castToType), toType(castToType), fromValue(castFromValue) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string getName() override;
    json::value asJsonStr() override;
    ~LgsCast() override;
};


