#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsNullable.h"

class LgsNull final : public LgsExpr {
public:
    static constexpr auto nullLiteral = "null";
    explicit LgsNull() : LgsExpr(new LgsNullable(nullptr)) {}
    json::value asJsonStr() override;
    std::string getName() override;
    ~LgsNull() override;
};

