#include "exprs/unary/LgsVectorExpr.h"

void LgsVectorExpr::createIRValue(LgsCodeGen* codeGen) {
    const auto ty = type->getIRType(codeGen);
    IRValue = codeGen->builder.CreateAlloca(ty);
    codeGen->builder.CreateStore(ConstantAggregateZero::get(ty), IRValue);
}

std::string LgsVectorExpr::pname() {
    return "vec2";
}

auto LgsVectorExpr::asJSON() -> json::value {
    json::object obj;
    return obj;
}

LgsVectorExpr::~LgsVectorExpr() {
    for (const auto & arg : args) {
        delete arg;
    }
    args.clear();
}