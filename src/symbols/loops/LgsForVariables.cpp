#include "loops/LgsLoopMetaVar.h"

Value* LgsLoopMetaVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

std::string LgsLoopMetaVar::getName() {
    return name;
}