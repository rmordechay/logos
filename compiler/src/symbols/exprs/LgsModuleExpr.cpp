#include "exprs/LgsModuleExpr.h"

#include <assert.h>

void LgsModuleExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsModuleExpr::asText() {
    return name;
}
