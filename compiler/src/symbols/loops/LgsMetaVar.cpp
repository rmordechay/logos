#include "loops/LgsMetaVar.h"
#include "codegen/LgsCodeGen.h"

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
