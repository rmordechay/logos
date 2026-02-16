#include "exprs/LgsMatrixExpr.h"

#include "exprs/LgsArrayExpr.h"

std::string LgsMatrixExpr::asText() {
    assert(0);
}

void LgsMatrixExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

void LgsMatrixExpr::hashNode(size_t& oldHash) {
    assert(0);
}

bool LgsMatrixExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsMatrixExpr::~LgsMatrixExpr() {
    for (const auto element : elements) {
        freeExpr(element);
    }
    elements.clear();
}
