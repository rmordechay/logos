#include "loops/LgsLoopMetaVar.h"

Value* LgsLoopMetaVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsLoopMetaVar* LgsLoopMetaVar::cloneExpr() {
    return new LgsLoopMetaVar(*this);
}

std::string LgsLoopMetaVar::asText() {
    return name;
}
