#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsSwitch final : public LgsStmt {
public:
    LgsExpr* cond;
    LgsStmtsBlock* elseBlock = nullptr;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> patterns;

    explicit LgsSwitch(LgsExpr* cond): cond(cond){}
    void parseAsJSON(std::stringstream& json) override;
    ~LgsSwitch() override;
};
