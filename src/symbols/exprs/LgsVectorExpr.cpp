#include "exprs/LgsVectorExpr.h"

Value* LgsVectorExpr::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(vecType->getIRType(cg), IRValue);
}

std::string LgsVectorExpr::asText() {
    return vecType->pname();
}

LgsVectorExpr::~LgsVectorExpr() {
    for (const auto & arg : args) {
        delete arg;
    }
    args.clear();
}
