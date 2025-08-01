#pragma once
#include "stmts/LgsStmt.h"

class LgsStmtsBlock final : public LgsValue {
public:
    vector<LgsStmt*> stmts;
    vector<LgsExpr*> returnExprs;
    vector<LgsExpr*> heapAllocExprs;
    BasicBlock* cleanupBlock = nullptr;
    PHINode* returnPhiNode = nullptr;
    bool hasReturn = false;

    explicit LgsStmtsBlock(const vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    bool needsCleanup() const;
    void createIRValue(LgsCodeGen* codeGen);
    void cleanup(LgsCodeGen* codeGen) const;
    void initCleanup(LgsCodeGen* codeGen);
    LgsStmt* lastStmt() const;
    string format(string& indentStr) override;
    ~LgsStmtsBlock() override;
};
