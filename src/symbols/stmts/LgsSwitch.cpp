#include "stmts/LgsSwitch.h"
#include "stmts/LgsStmtsBlock.h"
#include "utils/LgsUtils.h"

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
