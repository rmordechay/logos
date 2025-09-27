#pragma once

#include "funcs/LgsFunc.h"

class LgsIterator final : public LgsExpr {
public:
    static constexpr auto name = "Iterator";
    LgsExpr* baseExpr;

    explicit LgsIterator(LgsExpr* baseExpr) : baseExpr(baseExpr) {
        type = baseExpr->type;
    }
    std::string pname() override;
    json::value asJsonStr() override;
};

