#include "exprs/unary/LgsVectorExpr.h"

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