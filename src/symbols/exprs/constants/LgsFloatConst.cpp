#include "exprs/constants/LgsFloatConst.h"

#include "LgsType.h"
#include "codegen/LgsLLVMGen.h"

Value* LgsFloatConst::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsFloatConst::getName() {
    return std::to_string(value);
}
