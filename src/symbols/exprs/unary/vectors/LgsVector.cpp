#include "exprs/unary/vectors/LgsVector.h"

void LgsVector::createIRValue(LgsCodeGen* codeGen) {
    const auto ty = type->getIRType(codeGen);
    IRValue = codeGen->builder.CreateAlloca(ty);
}

std::string LgsVector::prettyName() {
    return "vec2";
}
