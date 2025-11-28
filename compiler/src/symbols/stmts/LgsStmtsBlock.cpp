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
        case LgsObjOrStmt::Type::Object:
            freeType(stmt.obj);
            break;
        case LgsObjOrStmt::Type::Stmt:
            freeStmt(stmt.stmt);
            break;
        }
    }
    stmts.clear();
}
