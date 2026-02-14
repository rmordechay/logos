#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsDeferStmt final : public LgsStmt {
public:
    LgsExpr* expr = nullptr;

    void setDebugValue(LgsCodeGen& cg) override;
    LgsFuncCall* getAsFuncCall() const;
    ~LgsDeferStmt() override;
};
