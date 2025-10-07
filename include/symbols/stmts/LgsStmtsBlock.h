#pragma once
#include "stmts/LgsStmt.h"

namespace llvm {
    class BasicBlock;
}

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmt*> stmts;
    LgsReturn* returnExpr = nullptr;

    explicit LgsStmtsBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    LgsStmt* lastStmt() const;
    void parseAsJSON(std::stringstream& json) override;
    ~LgsStmtsBlock() override;
};
