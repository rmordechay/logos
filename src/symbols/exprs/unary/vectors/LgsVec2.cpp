#include "exprs/unary/vectors/LgsVec2.h"

void LgsVec2::createIRValue(LgsCodeGen* codeGen) {
    IRValue = codeGen->builder.CreateAlloca(type->getIRType(codeGen));
}

std::string LgsVec2::prettyName() {
    return "vec2";
}
