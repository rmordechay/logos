#pragma once
#include "types/LgsAny.h"
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/primitives/LgsBool.h"
#include "types/LgsVoid.h"
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

