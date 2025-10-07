#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsReturn.h"
#include "utils/LgsUtils.h"

LgsStmt* LgsStmtsBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

void LgsStmtsBlock::parseAsJSON(std::stringstream& json) {
    openJsonArray(json);
    bool first = true;
    for (const auto stmt : stmts) {
        if (!first) json << ',';
        first = false;
        stmt->parseAsJSON(json);
    }
    closeJsonArray(json);
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
    stmts.clear();
}
