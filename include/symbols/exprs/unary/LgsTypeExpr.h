#pragma once
#include "LgsUnaryExpr.h"

class LgsTypeExpr final : public LgsUnaryExpr {
public:
    explicit LgsTypeExpr(LgsType* type): LgsUnaryExpr(type) {}
    json::value asJSON() override;
    std::string pname() override;
};
