#pragma once

#include "types/iterables/LgsVec.h"

class LgsVectorExpr final : public LgsExpr {
public:
    LgsVec* vecType;
    std::vector<LgsExpr*> elements;

    explicit LgsVectorExpr(const int8_t dim) {
        vecType = new LgsVec(dim);
        setType(vecType);
    }

    explicit LgsVectorExpr(LgsVec* vecType): vecType(vecType) {}
    Value* loadIR(LgsLLVMGen& cg) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    ~LgsVectorExpr() override;
};
