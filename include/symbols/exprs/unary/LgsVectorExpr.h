#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsVec.h"

class LgsVectorExpr final : public LgsUnaryExpr {
public:
    size_t dim = 0;
    std::vector<LgsExpr*> args;

    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    std::string pname() override;
    ~LgsVectorExpr() override;
};
