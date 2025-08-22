#include "stmts/LgsStmtsBlock.h"
#include "configs/LgsDefinitions.h"
#include "exprs/unary/LgsSelection.h"
#include "funcs/LgsFunc.h"
#include "stmts/LgsReturn.h"

void LgsStmtsBlock::createIRValue(LgsCodeGen* codeGen) {
    for (const auto stmt : stmts) {
        stmt->createIRValue(codeGen);
    }
}

LgsStmt* LgsStmtsBlock::lastStmt() const {
    if (stmts.empty()) return nullptr;
    return stmts[stmts.size() - 1];
}

json::value LgsStmtsBlock::asJSON() {
    json::array jsonStmts;
    for (const auto& stmt : stmts) {
        jsonStmts.emplace_back(stmt->asJSON());
    }
    return jsonStmts;
}

LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        delete stmt;
    }
    stmts.clear();
}
