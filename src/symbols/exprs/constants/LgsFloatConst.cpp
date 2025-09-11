#include "exprs/constants/LgsFloatConst.h"

#include "LgsType.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsFloatConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}


json::value LgsFloatConst::asJSON() {
    assert(0);
}

std::string LgsFloatConst::pname() {
    return std::to_string(value);
}
