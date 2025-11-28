#include "loops/LgsMetaVar.h"

Value* LgsMetaVar::loadIR(LgsCgModule& cg) {
    return IRValue;
}

Value* LgsMetaVar::castIR(LgsCgModule& cg, LgsType* toType) {
    assert(0);
}

bool LgsMetaVar::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsMetaVar::asText() {
    return name;
}
