#include "exprs/LgsVectorExpr.h"

#include "LgsUtils.h"

Value* LgsVectorExpr::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(vecType->getIRType(cg), IRValue);
}

void LgsVectorExpr::setDebugValue(LgsLLVMGen& cg) {
    assert(0);
}

void LgsVectorExpr::hashNode(size_t& oldHash) {
    assert(0);
}

LgsExpr* LgsVectorExpr::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsVectorExpr::castImplicitly(LgsType* toType) {
    assert(0);
}

Value* LgsVectorExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    return IRValue;
}

Value* LgsVectorExpr::hashValue(LgsLLVMGen& cg) {
    assert(0);
}

LgsExpr* LgsVectorExpr::clone() {
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
