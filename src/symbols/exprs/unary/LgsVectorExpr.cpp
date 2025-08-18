#include "exprs/unary/LgsVectorExpr.h"

json::object LgsVectorExpr::asJSON() {
    json::object obj;
    return obj;
}

void LgsVectorExpr::createIRValue(LgsCodeGen* codeGen) {
    const auto ty = type->getIRType(codeGen);
    IRValue = codeGen->builder.CreateAlloca(ty);
}

std::string LgsVectorExpr::pname() {
    return "vec2";
}
