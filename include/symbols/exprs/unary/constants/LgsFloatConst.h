#pragma once
#include "exprs/LgsExpr.h"

class LgsFloatConst final : public LgsExpr {
public:
    double_t value;

    explicit LgsFloatConst(LgsType* type, const double_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    json::value asJSON() override;
    std::string pname() override;
    ~LgsFloatConst() override = default;
};
