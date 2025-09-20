#pragma once
#include "exprs/LgsExpr.h"

class LgsIntConst final : public LgsExpr {
public:
    uint64_t value;

    LgsIntConst(LgsType* type, const size_t value) : LgsExpr(type), value(value) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    LgsExpr* castTo(LgsType* toType) override;
    std::string pname() override;
    json::value asJSON() override;
};
