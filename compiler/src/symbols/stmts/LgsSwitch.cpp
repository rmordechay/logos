#include "stmts/LgsSwitch.h"
#include "stmts/LgsStmtsBlock.h"
#include "LgsUtils.h"
#include "exprs/LgsExpr.h"

void LgsSwitch::setDebugValue(LgsCodeGen& cg) {
    assert(0);
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
