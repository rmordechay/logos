#pragma once

#include "types/iterables/LgsVec.h"

class LgsVectorExpr final : public LgsExpr {
public:
    LgsVec* vecType;
    std::vector<LgsExpr*> args;

    explicit LgsVectorExpr(const int8_t dim) {
        isMutable = true;
        vecType = new LgsVec(dim);
        type = vecType;
    }

    explicit LgsVectorExpr(LgsVec* vecType): vecType(vecType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string getName() override;
    ~LgsVectorExpr() override;
};
