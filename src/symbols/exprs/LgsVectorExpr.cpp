#include "exprs/LgsVectorExpr.h"

Value* LgsVectorExpr::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(vecType->getIRType(cg), IRValue);
}

std::string LgsVectorExpr::pname() {
    return vecType->pname();
}

auto LgsVectorExpr::asJsonStr() -> json::value {
    json::object obj;
    return obj;
}

LgsVectorExpr::~LgsVectorExpr() {
    for (const auto & arg : args) {
        delete arg;
    }
    args.clear();
}
