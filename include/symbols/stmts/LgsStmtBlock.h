#pragma once
#include "stmts/LgsStmt.h"

class LgsStmtBlock final : public LgsValue {
public:
    std::vector<LgsStmt*> stmts;
    bool hasReturn = false;

    explicit LgsStmtBlock(const std::vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    void createIRValue(LgsRuntime* runtime) const;
    LgsStmt* lastStmt() const;
    std::string format(std::string& indentStr) override;
    nlohmann::json asJSON() override;
    ~LgsStmtBlock() override;
};



