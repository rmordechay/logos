#include "exprs/LgsMatrixExpr.h"

#include "exprs/LgsArrayExpr.h"

std::string LgsMatrixExpr::asText() {
    assert(0);
}

Value* LgsMatrixExpr::loadIR(LgsLLVMGen& cg) {
    assert(0);
}

void LgsMatrixExpr::setDebugValue(LgsLLVMGen& cg) {
    assert(0);
}

void LgsMatrixExpr::hashNode(size_t& oldHash) {
    assert(0);
}

LgsExpr* LgsMatrixExpr::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsMatrixExpr::castImplicitly(LgsType* toType) {
    if (type->getName() == toType->getName()) return;
    assert(0);
}

Value* LgsMatrixExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

Value* LgsMatrixExpr::hashValue(LgsLLVMGen& cg) {
    assert(0);
}

bool LgsMatrixExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsExpr* LgsMatrixExpr::clone() {
    assert(0);
}

LgsMatrixExpr::~LgsMatrixExpr() {
    for (const auto element : elements) {
        freeExpr(element);
    }
    elements.clear();
}
