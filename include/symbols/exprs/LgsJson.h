#pragma once
#include "LgsExpr.h"

class LgsNull;

class LgsJson final : public LgsExpr {
public:
    LgsInstance* instance = nullptr;
    LgsArrayExpr* arr = nullptr;
    LgsStrConst* strConst = nullptr;
    LgsIntConst* intConst = nullptr;
    LgsFloatConst* floatConst = nullptr;
    LgsNull* null = nullptr;
    json::value asJsonStr() override;
    ~LgsJson() override = default;
};

inline json::value LgsJson::asJsonStr() {
    assert(0);
}
