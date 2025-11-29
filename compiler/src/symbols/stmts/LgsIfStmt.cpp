#include "stmts/LgsIfStmt.h"
#include "codegen/LgsCgModule.h"
#include "LgsUtils.h"

LgsIfStmt::~LgsIfStmt() {
    freeExpr(ifCond);
    ifCond = nullptr;
    if (ifBlock) {
        delete ifBlock;
        ifBlock = nullptr;
    }
    if (elseBlock) {
        delete elseBlock;
        elseBlock = nullptr;
    }
    for (const auto& [expr, block] : elseIfs) {
        freeExpr(expr);
        delete block;
    }
    elseIfs.clear();
}

