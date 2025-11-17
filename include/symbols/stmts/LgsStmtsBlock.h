#pragma once
#include "stmts/LgsStmt.h"
#include "types/LgsObject.h"

namespace llvm {
    class BasicBlock;
}

class LgsObjOrStmt {
public:
    enum class Type { Object, Stmt };
    Type type;
    union {
        LgsObject* obj;
        LgsStmt* stmt;
    };
    explicit LgsObjOrStmt(LgsObject* o) : type(Type::Object), obj(o) {}
    explicit LgsObjOrStmt(LgsStmt* s) : type(Type::Stmt), stmt(s) {}

};

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsObjOrStmt> stmts;
    LgsReturn* returnStmt = nullptr;

    explicit LgsStmtsBlock(const std::vector<LgsObjOrStmt>& stmts = {}) : stmts(stmts) {}
    LgsStmtsBlock* clone() override;
    void hashNode(size_t& oldHash) override;
    ~LgsStmtsBlock() override;
};
