#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsPatternMatch final : public LgsStmt {
public:
    LgsExpr* cond;
    LgsStmtsBlock* elseBlock = nullptr;
    std::vector<std::pair<LgsExpr*, LgsStmtsBlock*>> patterns;

    explicit LgsPatternMatch(LgsExpr* cond = nullptr): cond(cond){}
    void parseAsJSON(std::stringstream& json) override;
    ~LgsPatternMatch() override;
};
