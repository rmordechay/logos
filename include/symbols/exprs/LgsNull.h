#pragma once
#include "exprs/LgsExpr.h"

class LgsNull final : public LgsExpr {
public:
    explicit LgsNull() : LgsExpr(nullptr) {
        isNull = true;
    }

    json::value asJsonStr() override;
    std::string pname() override;
};

inline json::value LgsNull::asJsonStr() {
    return json::value(nullptr);
}

inline std::string LgsNull::pname() {
    return "null";
}
