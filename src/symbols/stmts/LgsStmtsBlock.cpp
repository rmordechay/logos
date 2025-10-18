#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsReturn.h"
#include "utils/LgsUtils.h"

LgsStmt* LgsStmtsBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
    stmts.clear();
}
