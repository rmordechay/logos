#pragma once
#include "exprs/LgsExpr.h"
#include "types/LgsComplex.h"

class LgsComplexConst final : public LgsExpr {
public:
    LgsExpr* real;
    LgsExpr* imaginary;

    LgsComplexConst(LgsExpr* real, LgsExpr* imaginary): real(real), imaginary(imaginary) {}
    void setDebugValue(LgsCgModule& cg) override;
    Value* loadIR(LgsCgModule& cg) override;
    std::string asText() override;
    ~LgsComplexConst() override;
};
