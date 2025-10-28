#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsReturn.h"
#include "utils/LgsUtils.h"

LgsStmt* LgsStmtsBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

LgsStmtsBlock* LgsStmtsBlock::clone() const {
    const auto cloned = new LgsStmtsBlock();
    cloned->location = location;
    cloned->stmts.reserve(stmts.size());
    for (const auto stmt : stmts) {
        cloned->stmts.push_back(stmt->cloneStmt());
    }
    cloned->returnStmt = returnStmt ? dynamic_cast<LgsReturn*>(returnStmt->cloneStmt()) : nullptr;
    return cloned;
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        freeStmt(stmt);
    }
    stmts.clear();
}
