#pragma once
#include "LgsExpr.h"
#include "types/iterables/LgsMatrix.h"

class LgsMatrixExpr final : public LgsExpr {
public:
    std::vector<LgsArrayExpr*> elements;
    LgsMatrix* matType = nullptr;

    LgsMatrixExpr(const size_t rows, const size_t columns) {
        matType = new LgsMatrix(rows, columns);
        type = matType;
    }
    std::string asText() override;
    Value* loadIR(LgsLLVMGen& cg) override;
    void setDebugValue(LgsLLVMGen& cg) override;
    void hashNode(size_t& oldHash) override;
    LgsExpr* castExplicitly(LgsType* toType) override;
    void castImplicitly(LgsType* toType) override;
    Value* castIR(LgsLLVMGen& cg, LgsType* toType) override;
    Value* hashValue(LgsLLVMGen& cg) override;
    bool equals(LgsExpr* other) override;
    LgsExpr* clone() override;
    ~LgsMatrixExpr() override;
};
