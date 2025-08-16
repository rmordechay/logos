#pragma once
#include "LgsVec.h"
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec2 final : public LgsVec {
public:
    LgsExpr* x = nullptr;
    LgsExpr* y = nullptr;

    void createIRValue(LgsCodeGen* codeGen) override;
    std::string prettyName() override;
    ~LgsVec2() override = default;
};


