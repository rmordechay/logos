#pragma once
#include "stmts/LgsStmt.h"

class LgsStmtsBlock final : public LgsValue {
public:
    vector<LgsStmt*> stmts;
    vector<LgsExpr*> heapAllocExprs;
    bool hasReturn = false;

    explicit LgsStmtsBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    void createIRValue(LgsCodeGen* codeGen) const;
    void cleanup(LgsCodeGen* codeGen) const;
    LgsStmt* lastStmt() const;
    std::string format(std::string& indentStr) override;
    ~LgsStmtsBlock() override;
};
