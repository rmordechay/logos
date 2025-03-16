#ifndef LOGOSSTMTBLOCK_H
#define LOGOSSTMTBLOCK_H
#include "stmts/LgsStmt.h"

class LgsStmtBlock final : public LgsValue {
public:
    vector<LgsStmt*> stmts;

    explicit LgsStmtBlock(const vector<LgsStmt*>& stmts) : stmts(stmts) {}
    Value* createIRValue(CodeGenMetadata* metadata) override;
    ~LgsStmtBlock() override = default;
    LgsStmtBlock();
};


#endif //LOGOSSTMTBLOCK_H
