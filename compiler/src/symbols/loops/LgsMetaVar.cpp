#include "loops/LgsMetaVar.h"

#include <assert.h>

bool LgsMetaVar::equals(LgsExpr* other) {
    assert(0);
}

std::string LgsMetaVar::asText() {
    return name;
}

void LgsMetaVar::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

LgsExpr* LgsMetaVar::clone() const {
    return new LgsMetaVar(*this);
}
