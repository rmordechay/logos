#include "exprs/constants/LgsCharConst.h"

Value* LgsCharConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

Value* LgsCharConst::castIR(LgsLLVMGen& cg, LgsType* toType) {
    assert(0);
}

std::string LgsCharConst::asText() {
    return type->pname();
}
