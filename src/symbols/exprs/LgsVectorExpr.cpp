#include "exprs/LgsVectorExpr.h"

#include "utils/LgsUtils.h"

Value* LgsVectorExpr::loadIR(LgsLLVMGen& cg) {
    return cg.builder.CreateLoad(vecType->getIRType(cg), IRValue);
}

std::string LgsVectorExpr::asText() {
    return vecType->pname();
}

bool LgsVectorExpr::equals(LgsExpr* other) {
    assert(0);
}

LgsVectorExpr::~LgsVectorExpr() {
    for (const auto & arg : args) {
        freeExpr(arg);
    }
    args.clear();
}
