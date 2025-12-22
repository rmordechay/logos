#include "exprs/LgsVectorExpr.h"
#include "LgsUtils.h"

Value* LgsVectorExpr::loadIR(LgsCgModule& cg) {
    return cg.load(vecType->getIRType(cg), IRValue);
}

void LgsVectorExpr::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

void LgsVectorExpr::hashNode(size_t& oldHash) {
    assert(0);
}

LgsExpr* LgsVectorExpr::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsVectorExpr::castImplicitly(LgsType* toType) {

}

Value* LgsVectorExpr::hashValue(LgsCgModule& cg) {
    assert(0);
}

std::string LgsVectorExpr::asText() {
    return vecType->pname();
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
