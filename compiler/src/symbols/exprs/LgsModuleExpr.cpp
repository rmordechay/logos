#include "exprs/LgsModuleExpr.h"

LgsExpr* LgsModuleExpr::cast(const bool explicitly) {
    return this;
}

void LgsModuleExpr::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}

std::string LgsModuleExpr::asText() {
    return name;
}
