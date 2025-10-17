#include "loops/LgsLoopMetaVar.h"

Value* LgsLoopMetaVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsLoopMetaVar::asText() {
    return name;
}