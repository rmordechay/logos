#pragma once
#include "LgsStmt.h"

class LgsIOPair;
class LgsStmtsBlock;

class LgsIOStmt final : public LgsStmt {
public:
    LgsStmtsBlock* stmtsBlock = nullptr;
    LgsVarDec* varDec = nullptr;
    LgsFunc* closingFunc = nullptr;

    LgsIOStmt() = default;
    explicit LgsIOStmt(LgsStmtsBlock* stmtsBlock): stmtsBlock(stmtsBlock) {}
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsIOStmt() override;
};
