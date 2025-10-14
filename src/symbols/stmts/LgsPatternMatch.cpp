#include "stmts/LgsPatternMatch.h"
#include "stmts/LgsStmtsBlock.h"
#include "utils/LgsUtils.h"

void LgsPatternMatch::parseAsJSON(std::stringstream& json) {
    openJsonObject(json);
    addJsonKeyValue(json, "kind", "PatternMatch", true);
    closeJsonObject(json);
}

LgsPatternMatch::~LgsPatternMatch() {
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
