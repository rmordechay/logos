#include "exprs/unary/vectors/LgsVector.h"

void LgsVector::createIRValue(LgsCodeGen* codeGen) {
    const auto ty = type->getIRType(codeGen);
    IRValue = codeGen->builder.CreateAlloca(ty);
}

LgsField* LgsVector::getScalars(const std::string& fieldName) {
    assert(0);
}

std::string LgsVector::pname() {
    return "vec2";
}
