#include "stmts/LgsStmtBlock.h"
#include "exprs/unary/LgsSelection.h"

void LgsStmtBlock::createIRValue(LgsModule* runtime) const {
    for (const auto stmt : stmts) {
        stmt->createIRStmt(runtime);
    }
}

LgsStmt* LgsStmtBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

std::string LgsStmtBlock::format(std::string& indentStr) {
    std::stringstream oss;
    oss << " {\n";
    indentStr += '\t';
    for (const auto& stmt : stmts) {
        oss << stmt->format(indentStr) << '\n';
    }
    oss << "}\n\n";
    return oss.str();
}

LgsStmtBlock::~LgsStmtBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
