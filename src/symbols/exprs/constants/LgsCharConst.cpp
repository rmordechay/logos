#include "exprs/constants/LgsCharConst.h"

Value* LgsCharConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsCharConst::getName() {
    return type->pname();
}

json::value LgsCharConst::asJsonStr() {
    assert(0);
}
