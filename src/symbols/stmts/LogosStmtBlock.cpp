#include "stmts/LogosStmtBlock.h"

Value* LogosStmtBlock::getLLVMValue(CodeGenMetadata* metadata) {
    for (const auto stmt : stmts) {
        stmt->getLLVMValue(metadata);
    }
    return nullptr;
}

LogosStmtBlock::LogosStmtBlock() {
    for (const auto stmt : stmts) {
        delete stmt;
    }
}
