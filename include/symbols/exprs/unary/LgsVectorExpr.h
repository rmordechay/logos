#pragma once
#include "exprs/unary/LgsUnaryExpr.h"
#include "types/LgsVec.h"

class LgsVectorExpr final : public LgsUnaryExpr {
public:
    std::vector<LgsExpr*> args;
    LgsVec* vecType;

    LgsVectorExpr(const int8_t dim) {
        isMutable = true;
        vecType = new LgsVec(dim);
        type = vecType;
    }

    explicit LgsVectorExpr(LgsVec* vecType): vecType(vecType) {}
    Value* loadIR(LgsLLVM& codeGen) override;
    std::string pname() override;
    json::value asJSON() override;
    ~LgsVectorExpr() override;
};
