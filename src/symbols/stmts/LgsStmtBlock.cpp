#include "stmts/LgsStmtBlock.h"

#include "stmts/LgsReturn.h"

void LgsStmtBlock::createIRValue(CodeGenMetadata* metadata) const {
    for (const auto& stmt : stmts) {
        stmt->createIRValue(metadata);
    }
}

LgsStmt* LgsStmtBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

LgsStmtBlock::~LgsStmtBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
