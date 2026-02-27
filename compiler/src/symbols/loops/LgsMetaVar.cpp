#include "loops/LgsMetaVar.h"

#include <assert.h>

std::string LgsMetaVar::asText() {
    return name;
}

void LgsMetaVar::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsMetaVar::clone() const {
    return new LgsMetaVar(*this);
}
