#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsSwitch final : public LgsStmt {
public:
    LgsExpr* cond;
    LgsStmtsBlock* elseBlock = nullptr;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> patterns;
    bool isExhausted = false;

    explicit LgsSwitch(LgsExpr* cond): cond(cond){}
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsSwitch() override;
};
