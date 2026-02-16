#include "exprs/LgsVectorExpr.h"
#include "LgsUtils.h"

void LgsVectorExpr::setType(LgsType* newType) {
    vecType = newType->asVec();
    type = vecType;
}

void LgsVectorExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

void LgsVectorExpr::hashNode(size_t& oldHash) {
    assert(0);
}

std::string LgsVectorExpr::asText() {
    return type->pname();
}

bool LgsVectorExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsVectorExpr::~LgsVectorExpr() {
    for (const auto & arg : elements) {
        freeExpr(arg);
    }
    elements.clear();
}
