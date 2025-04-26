#include "stmts/LgsStmtBlock.h"

#include "exprs/unary/LgsSelection.h"
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

string LgsStmtBlock::format(string& indentStr) {
    stringstream oss;
    oss << " {\n";
    indentStr += '\t';
    for (const auto& stmt : stmts) {
        oss << stmt->format(indentStr) << '\n';
    }
    oss << "}\n\n";
    return oss.str();
}

json LgsStmtBlock::asJSON() {
    json tree;
    for (const auto& stmt : stmts) {
        tree["stmts"].emplace_back(stmt->asJSON());
    }
    return tree;
}

LgsStmtBlock::~LgsStmtBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
}
