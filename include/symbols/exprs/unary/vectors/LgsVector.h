#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsVec2.h"

class LgsVector final : public LgsUnaryExpr {
public:
    size_t vecSize = 0;
    std::vector<LgsExpr*> args;

    void createIRValue(LgsCodeGen* codeGen) override;
    std::string prettyName() override;
    ~LgsVector() override = default;
};
