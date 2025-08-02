#pragma once
#include "stmts/LgsStmt.h"

class LgsStmtsBlock final : public LgsValue {
public:
    vector<LgsStmt*> stmts;
    vector<LgsExpr*> heapAllocExprs;
    BasicBlock* cleanupBlock = nullptr;
    bool hasReturn = false;

    explicit LgsStmtsBlock(const vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    bool needsCleanup() const;
    BasicBlock* getCleanupBlock(LgsCodeGen* codeGen);
    void createIRValue(LgsCodeGen* codeGen);
    LgsStmt* lastStmt() const;
    string format(string& indentStr) override;
    ~LgsStmtsBlock() override;
};
