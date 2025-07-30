#include "stmts/LgsStmtsBlock.h"
#include "exprs/unary/LgsSelection.h"

void LgsStmtsBlock::createIRValue(LgsCodeGen* codeGen) const {
    for (const auto stmt : stmts) {
        stmt->createIRStmt(codeGen);
    }
}

LgsStmt* LgsStmtsBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

std::string LgsStmtsBlock::format(std::string& indentStr) {
    std::stringstream oss;
    oss << " {\n";
    indentStr += '\t';
    for (const auto& stmt : stmts) {
        oss << stmt->format(indentStr) << '\n';
    }
    oss << "}\n\n";
    return oss.str();
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
