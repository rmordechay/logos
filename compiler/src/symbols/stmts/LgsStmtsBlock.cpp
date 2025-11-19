#include "stmts/LgsStmtsBlock.h"
#include "stmts/LgsReturn.h"
#include "LgsUtils.h"

LgsStmtsBlock* LgsStmtsBlock::clone() {
    const auto cloned = new LgsStmtsBlock();
    cloned->location = location;
    cloned->stmts.reserve(stmts.size());
    for (const auto stmt : stmts) {
        switch (stmt.type) {
        case LgsObjOrStmt::Type::Object:
            cloned->stmts.push_back(LgsObjOrStmt(stmt.obj->clone()));
            break;
        case LgsObjOrStmt::Type::Stmt:
            cloned->stmts.push_back(LgsObjOrStmt(stmt.stmt->clone()));
            break;
        }
    }
    cloned->returnStmt = returnStmt ? dynamic_cast<LgsReturn*>(returnStmt->clone()) : nullptr;
    return cloned;
}

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
