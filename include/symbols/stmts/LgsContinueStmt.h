#pragma once
#include "LgsStmt.h"

class LgsContinueStmt final : public LgsStmt {
public:
    void createIRStmt(LgsModule* module) override;
    ~LgsContinueStmt() override = default;
};



