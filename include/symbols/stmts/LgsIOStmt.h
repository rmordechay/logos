#pragma once
#include "LgsStmt.h"

class LgsIOPair;
class LgsStmtsBlock;

class LgsIOStmt final : public LgsStmt {
public:
    LgsStmtsBlock* stmtsBlock;
    LgsVarDec* varDec = nullptr;
    LgsFunc* closingFunc = nullptr;

    explicit LgsIOStmt(LgsStmtsBlock* stmtsBlock): stmtsBlock(stmtsBlock) {}
    json::value asJsonStr() override;
    ~LgsIOStmt() override;
};
