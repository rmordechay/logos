#include "exprs/LgsNullableExpr.h"
#include "codegen/LgsCgModule.h"

std::string LgsNullableExpr::asText() {
    assert(0);
}

Value* LgsNullableExpr::loadIR(LgsCgModule& cg) {
    return cg.builder.CreateLoad(type->getIRType(cg), IRValue);
}

void LgsNullableExpr::setDebugValue(LgsCgModule& cg) {
    assert(0);
}

void LgsNullableExpr::hashNode(size_t& oldHash) {
    assert(0);
}

LgsExpr* LgsNullableExpr::castExplicitly(LgsType* toType) {
    assert(0);
}

void LgsNullableExpr::castImplicitly(LgsType* toType) {

}

Value* LgsNullableExpr::hashValue(LgsCgModule& cg) {
    assert(0);
}

 bool LgsNullableExpr::equals(LgsExpr* other) {
    assert(0);
}