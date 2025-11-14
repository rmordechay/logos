#pragma once
#include "stmts/LgsStmt.h"
#include "types/LgsObject.h"

namespace llvm {
    class BasicBlock;
}

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmt*> stmts;
    LgsReturn* returnStmt = nullptr;

    explicit LgsStmtsBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    LgsStmtsBlock* clone() const;
    void hashNode(size_t& oldHash) override;
    ~LgsStmtsBlock() override;
};
