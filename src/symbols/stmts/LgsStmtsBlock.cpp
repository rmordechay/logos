#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsReturn.h"
#include "utils/LgsUtils.h"

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

void LgsStmtsBlock::hashNode(size_t& oldHash) {
    for (const auto stmt : stmts) {
        stmt->hashNode(oldHash);
    }
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        freeStmt(stmt);
    }
    stmts.clear();
}
