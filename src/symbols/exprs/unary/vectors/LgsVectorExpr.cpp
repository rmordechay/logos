#include "exprs/unary/vectors/LgsVectorExpr.h"

void LgsVectorExpr::createIRValue(LgsCodeGen* codeGen) {
    const auto ty = type->getIRType(codeGen);
    IRValue = codeGen->builder.CreateAlloca(ty);
}

std::string LgsVectorExpr::pname() {
    return "vec2";
}
