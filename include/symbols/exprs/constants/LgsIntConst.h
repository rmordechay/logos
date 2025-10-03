#pragma once
#include "exprs/LgsExpr.h"

class LgsIntConst final : public LgsExpr {
public:
    int64_t value;

    LgsIntConst(LgsType* type, const size_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* castTo(LgsType* toType, bool explicitCast = false) override;
    std::string getName() override;
    LgsExpr* clone() override;
    json::value asJsonStr() override;
};
