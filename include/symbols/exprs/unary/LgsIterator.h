#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "funcs/LgsFunc.h"

class LgsIterator final : public LgsUnaryExpr {
public:
    static constexpr auto name = "Iterator";
    LgsExpr* baseExpr;

    explicit LgsIterator(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = baseExpr->type;
    }
    std::string pname() override;
    json::value asJSON() override;
};

