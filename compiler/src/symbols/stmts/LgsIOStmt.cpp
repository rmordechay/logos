#include "stmts/LgsIOStmt.h"

#include "stmts/LgsStmtsBlock.h"

LgsIOStmt::~LgsIOStmt() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
}

void LgsIOStmt::setDebugValue(LgsCodeGen& cg) {
    assert(0);
}
