#pragma once
#include "LgsStmt.h"

class LgsContinue final : public LgsStmt {
public:
    void createIRStmt(LgsCodeGen* codeGen) override;
    ~LgsContinue() override = default;
};



