#include "stmts/LgsStmtBlock.h"

Value* LgsStmtBlock::createIRValue(CodeGenMetadata* metadata) {
    for (const auto& stmt : stmts) {
        stmt->getIRValue(metadata);
    }
    return nullptr;
}

LgsStmtBlock::LgsStmtBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
