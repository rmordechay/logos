#include "stmts/LgsStmtBlock.h"

Value* LgsStmtBlock::createIRValue(CodeGenMetadata* metadata) const {
    for (const auto& stmt : stmts) {
        stmt->createIRValue(metadata);
    }
    return nullptr;
}

LgsStmtBlock::LgsStmtBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
