#include "loops/LgsMetaVar.h"
#include "codegen/LgsCodeGen.h"

Value* LgsMetaVar::loadIR(LgsCodeGen& cg) {
    return IRValue;
}

bool LgsMetaVar::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsMetaVar::asText() {
    return name;
}

void LgsMetaVar::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsMetaVar::clone() {
    return new LgsMetaVar(*this);
}
