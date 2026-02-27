#pragma once
#include <string>
#include <vector>

#include "LgsExpr.h"
#include "types/iterables/LgsMatrix.h"

class LgsArrayExpr;

class LgsMatrixExpr final : public LgsExpr {
public:
    LgsMatrix* matType = nullptr;
    std::vector<LgsExpr*> rows;

    LgsMatrixExpr(const size_t rows, const size_t columns) {
        setType(new LgsMatrix(rows, columns));
    }
    void setType(LgsType* newType) override;
    std::string asText() override;
    void setDebugValue(LgsCodeGen& cg) override;
    void hashNode(size_t& oldHash) override;
    ~LgsMatrixExpr() override;
};
