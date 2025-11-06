#include "loops/LgsMetaVar.h"

Value* LgsMetaVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsMetaVar* LgsMetaVar::cloneExpr() {
    return new LgsMetaVar(*this);
}

std::string LgsMetaVar::asText() {
    return name;
}
