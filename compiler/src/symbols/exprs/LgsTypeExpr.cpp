#include "exprs/LgsTypeExpr.h"

#include "LgsType.h"

Value* LgsTypeExpr::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

std::string LgsTypeExpr::asText() {
    return type->pname();
}
