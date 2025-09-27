#pragma once
#include "exprs/LgsExpr.h"

class LgsFloatConst final : public LgsExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    json::value asJsonStr() override;
    std::string getName() override;
    ~LgsFloatConst() override = default;
};
