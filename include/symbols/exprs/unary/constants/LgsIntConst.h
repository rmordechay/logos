#pragma once
#include "exprs/unary/LgsUnaryExpr.h"

class LgsIntConst final : public LgsUnaryExpr {
public:
    uint64_t value;

    LgsIntConst(LgsType* type, const size_t value) : LgsUnaryExpr(type), value(value) {}
    Value* loadIR(LgsLLVM& codeGen) override;
    LgsExpr* castTo(LgsType* toType) override;
    LgsExpr* clone() override;
    std::string pname() override;
    json::value asJSON() override;
};
