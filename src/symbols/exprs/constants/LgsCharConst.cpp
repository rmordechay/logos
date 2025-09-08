#include "exprs/constants/LgsCharConst.h"

Value* LgsCharConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsCharConst::pname() {
    return type->pname();
}

json::value LgsCharConst::asJSON() {
    assert(0);
}
