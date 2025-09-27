#include "stmts/LgsIOStmt.h"

#include "stmts/LgsIOPair.h"
#include "stmts/LgsStmtsBlock.h"

json::value LgsIOStmt::asJsonStr() {
    assert(0);
}

LgsIOStmt::~LgsIOStmt() {
    if (stmtsBlock) {
        delete stmtsBlock;
        stmtsBlock = nullptr;
    }
}
