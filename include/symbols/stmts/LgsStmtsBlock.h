#pragma once
#include "stmts/LgsStmt.h"

namespace llvm {
    class BasicBlock;
}

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmt*> stmts;
    std::vector<LgsExpr*> heapAllocExprs;
    llvm::BasicBlock* cleanupBlock = nullptr;
    LgsReturn* returnExpr = nullptr;

    explicit LgsStmtsBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    bool needsCleanup() const;
    LgsStmt* lastStmt() const;
    void cleanupExprs(LgsCodeGen* codeGen);
    llvm::BasicBlock* getCleanupBlock(LgsCodeGen* codeGen);
    void createIRValue(LgsCodeGen* codeGen) override;
    json::object asJSON() override;
    std::string format(std::string& indentStr) override;
    ~LgsStmtsBlock() override;
};
