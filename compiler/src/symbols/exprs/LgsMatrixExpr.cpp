#include "exprs/LgsMatrixExpr.h"

#include <assert.h>

#include "exprs/LgsArrayExpr.h"
#include "exprs/LgsExpr.h"

void LgsMatrixExpr::setType(LgsType* newType) {
    type = newType;
    matType = newType->asMatrix();
}

std::string LgsMatrixExpr::asText() {
    assert(0);
}

void LgsMatrixExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

void LgsMatrixExpr::hashNode(size_t& oldHash) {
    assert(0);
}

LgsMatrixExpr::~LgsMatrixExpr() {
    for (const auto element : rows) {
        freeExpr(element);
    }
    rows.clear();
}
