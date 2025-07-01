#pragma once
#include "LgsStmt.h"

class LgsContinueStmt final : public LgsStmt {
public:
    void createIRStmt(LgsModule* runtime) override;
    ~LgsContinueStmt() override = default;
};



