#pragma once
#include "LgsStmt.h"

class LgsIOPair;
class LgsStmtsBlock;

class LgsIOStmt final : public LgsStmt {
public:
    LgsStmtsBlock* stmtsBlock = nullptr;
    LgsVarDec* varDec = nullptr;
    LgsFunc* closeFunc = nullptr;

    LgsIOStmt() = default;
    explicit LgsIOStmt(LgsStmtsBlock* stmtsBlock): stmtsBlock(stmtsBlock) {}
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsIOStmt() override;
};
