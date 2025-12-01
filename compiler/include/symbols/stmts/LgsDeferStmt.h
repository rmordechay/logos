#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsDeferStmt final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;

    void setDebugValue(LgsCgModule& cg) override;
    ~LgsDeferStmt() override;
};
