#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsReturn.h"
#include "LgsUtils.h"

void LgsStmtsBlock::hashNode(size_t& oldHash) {
    for (const auto stmt : stmts) {
        stmt.stmt->hashNode(oldHash);
    }
}


LgsStmtsBlock::~LgsStmtsBlock() {
    for (const auto& stmt : stmts) {
        switch (stmt.type) {
        case LgsStmtWrapper::Type::Object:
            freeType(stmt.obj);
            break;
        case LgsStmtWrapper::Type::Stmt:
            freeStmt(stmt.stmt);
            break;
        case LgsStmtWrapper::Type::Expr:
            freeExpr(stmt.expr);
            break;
        }
    }
    stmts.clear();
}
