#pragma once
#include "stmts/LgsStmt.h"

namespace llvm {
    class BasicBlock;
}

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmt*> stmts;
    LgsReturn* returnStmt = nullptr;

    explicit LgsStmtsBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    LgsStmt* lastStmt() const;
    LgsStmtsBlock* clone() const;
    ~LgsStmtsBlock() override;
};
