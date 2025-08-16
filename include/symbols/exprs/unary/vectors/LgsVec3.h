#pragma once
#include "LgsVec.h"
#include "exprs/unary/LgsUnaryExpr.h"

class LgsVec3 final : public LgsVec {
public:
    LgsExpr* x = nullptr;
    LgsExpr* y = nullptr;
    LgsExpr* z = nullptr;

    void createIRValue(LgsCodeGen* codeGen) override;
    std::string prettyName() override;
    ~LgsVec3() override = default;
};


