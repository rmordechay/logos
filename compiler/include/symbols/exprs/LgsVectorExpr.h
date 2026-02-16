#pragma once
#include "types/iterables/LgsVec.h"

class LgsVectorExpr final : public LgsExpr {
public:
    size_t sumArgsDim = 0;
    LgsVec* vecType;
    std::vector<LgsExpr*> elements;

    explicit LgsVectorExpr(const int8_t dim): LgsVectorExpr(new LgsVec(dim)) {}
    explicit LgsVectorExpr(LgsVec* vec) {
        setType(vec);
    }
    void setType(LgsType* newType) override;
    void hashNode(size_t& oldHash) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsVectorExpr() override;
};
