#pragma once
#include "stmts/LgsStmt.h"
#include <llvm/IRReader/IRReader.h>

class LgsStmtsBlock final : public LgsValue {
public:
    std::vector<LgsStmt*> stmts;
    std::vector<LgsExpr*> heapAllocExprs;
    BasicBlock* cleanupBlock = nullptr;
    LgsReturn* returnExpr = nullptr;

    explicit LgsStmtsBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    bool needsCleanup() const;
    LgsStmt* lastStmt() const;
    void cleanupExprs(LgsCodeGen* codeGen);
    BasicBlock* getCleanupBlock(LgsCodeGen* codeGen);
    void createIRValue(LgsCodeGen* codeGen) override;
    std::string format(std::string& indentStr) override;
    ~LgsStmtsBlock() override;
};
