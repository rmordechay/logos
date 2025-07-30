#pragma once
#include "LgsStmt.h"

class LgsContinueStmt final : public LgsStmt {
public:
    void createIRStmt(LgsCodeGen* codeGen) override;
    ~LgsContinueStmt() override = default;
};



