#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsVec.h"

class LgsVectorExpr final : public LgsUnaryExpr {
public:
    size_t dim = 0;
    std::vector<LgsExpr*> args;

    LgsVectorExpr() {
        isMutable = true;
    }

    std::string pname() override;
    json::value asJSON() override;
    ~LgsVectorExpr() override;
};
