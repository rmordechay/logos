#include "stmts/LgsIOStmt.h"

#include "stmts/LgsStmtsBlock.h"

LgsIOStmt::~LgsIOStmt() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
}
