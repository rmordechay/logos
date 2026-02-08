#pragma once
#include "types/iterables/LgsVec.h"

class LgsVectorExpr final : public LgsExpr {
public:
    LgsVec* vecType;
    std::vector<LgsExpr*> elements;

    explicit LgsVectorExpr(const int8_t dim) {
        setType(new LgsVec(dim));
    }
    explicit LgsVectorExpr(LgsVec* vecType): LgsExpr(vecType), vecType(vecType) {}
    Value* loadIR(LgsCodeGen& cg) override;
    void setType(LgsType* newType) override;
    void hashNode(size_t& oldHash) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsVectorExpr() override;
};
