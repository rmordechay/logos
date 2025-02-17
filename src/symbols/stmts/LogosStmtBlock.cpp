#include "stmts/LogosStmtBlock.h"

Value* LogosStmtBlock::computeIRValue(CodeGenMetadata* metadata) {
    for (const auto& stmt : stmts) {
        stmt->getIRValue(metadata);
    }
    return nullptr;
}

LogosStmtBlock::LogosStmtBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
