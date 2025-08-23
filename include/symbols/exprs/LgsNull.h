#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsNull final : public LgsUnaryExpr {
public:
    explicit LgsNull() : LgsUnaryExpr(nullptr) {
        isNull = true;
    }

    json::value asJSON() override;
    std::string pname() override;
};

inline json::value LgsNull::asJSON() {
    return json::value(nullptr);
}

inline std::string LgsNull::pname() {
    return "null";
}
