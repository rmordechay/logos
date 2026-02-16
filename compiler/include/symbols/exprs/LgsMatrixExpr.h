#pragma once
#include "LgsExpr.h"
#include "types/iterables/LgsMatrix.h"

class LgsMatrixExpr final : public LgsExpr {
public:
    std::vector<LgsArrayExpr*> elements;
    LgsMatrix* matType = nullptr;

    LgsMatrixExpr(const size_t rows, const size_t columns) {
        matType = new LgsMatrix(rows, columns);
        setType(matType);
    }
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    void hashNode(size_t& oldHash) override;
    bool equals(LgsExpr* other) override;
    ~LgsMatrixExpr() override;
};
