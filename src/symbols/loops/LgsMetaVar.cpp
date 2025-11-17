#include "loops/LgsMetaVar.h"

Value* LgsMetaVar::loadIR(LgsLLVMGen& cg) {
    return IRValue;
}

LgsMetaVar* LgsMetaVar::clone() {
    return new LgsMetaVar(*this);
}

bool LgsMetaVar::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsMetaVar::asText() {
    return name;
}
