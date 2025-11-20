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
    void hashNode(size_t& oldHash) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* hashValue(LgsLLVMGen& cg) override;
    LgsExpr* clone() override;
    std::string asText() override;
    bool equals(LgsExpr* other) override;
    void setDebugValue(LgsLLVMGen& cg) override;
    ~LgsVectorExpr() override;
};
