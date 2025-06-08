#pragma once
#include "LgsStmt.h"

class LgsContinueStmt final : public LgsStmt {
public:
    void createIRStmt(LgsRuntime* runtime) override;
    ~LgsContinueStmt() override = default;
};



