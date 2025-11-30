#include "loops/LgsMetaVar.h"

Value* LgsMetaVar::loadIR(LgsCgModule& cg) {
    return IRValue;
}

bool LgsMetaVar::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsMetaVar::asText() {
    return name;
}
