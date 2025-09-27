#pragma once
#include "exprs/LgsExpr.h"


class LgsTypeExpr final : public LgsExpr {
public:
    explicit LgsTypeExpr(LgsType* type): LgsExpr(type) {}
    json::value asJsonStr() override;
    std::string pname() override;
};
