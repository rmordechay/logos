#include "stmts/LgsStmtBlock.h"

void LgsStmtBlock::createIRValue(CodeGenMetadata* metadata) const {
    for (const auto& stmt : stmts) {
        stmt->createIRValue(metadata);
    }
}

json LgsStmtBlock::asJson() {
    json tree = {};
    for (const auto& stmt : stmts) {
        tree.emplace_back(stmt->asJson());
    }
    return tree;
}

LgsStmtBlock::~LgsStmtBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
