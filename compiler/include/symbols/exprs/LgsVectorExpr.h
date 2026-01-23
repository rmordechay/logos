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
    explicit LgsVectorExpr(LgsVec* vecType): LgsExpr(vecType), vecType(vecType) {}
    Value* loadIR(LgsCodeGen& cg) override;
    void hashNode(size_t& oldHash) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsVectorExpr() override;
};
