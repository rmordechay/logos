#ifndef LOGOSSTMTBLOCK_H
#define LOGOSSTMTBLOCK_H
#include "stmts/LgsStmt.h"

class LgsStmtBlock final : public LgsValue {
public:
    vector<LgsStmt*> stmts;
    bool hasReturn = false;

    explicit LgsStmtBlock(const vector<LgsStmt*>& stmts = {}) : stmts(stmts) {}
    void createIRValue(CodeGenMetadata* metadata) const;
    LgsStmt* lastStmt() const;
    ~LgsStmtBlock() override;
};


#endif //LOGOSSTMTBLOCK_H
