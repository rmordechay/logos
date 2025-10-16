#include "stmts/LgsSwitch.h"
#include "stmts/LgsStmtsBlock.h"
#include "utils/LgsUtils.h"

void LgsSwitch::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "kind", "Switch", true);
    closeJsonObject(json);
}

LgsSwitch::~LgsSwitch() {
    if (cond) {
        freeExpr(cond);
        cond = nullptr;
    }
    if (elseBlock) {
        delete elseBlock;
        elseBlock = nullptr;
    }
    for (const auto& [expr, block] : patterns) {
        freeExpr(expr);
        delete block;
    }
    patterns.clear();
}
