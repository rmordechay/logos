#include "exprs/constants/LgsFloatConst.h"

#include "codegen/LgsLLVMGen.h"

Value* LgsFloatConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsFloatConst::asText() {
    return std::to_string(value);
}
