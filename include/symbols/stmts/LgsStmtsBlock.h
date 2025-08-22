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
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value asJSON() override;
    ~LgsStmtsBlock() override;
};
