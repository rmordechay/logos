#pragma once
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreak final : public LgsStmt {
public:
    string tag;
    void createIRStmt(LgsCodeGen* codeGen) override;
    ~LgsBreak() override = default;
};



