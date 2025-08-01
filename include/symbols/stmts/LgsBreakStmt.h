#pragma once
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreakStmt final : public LgsStmt {
public:
    string tag;

    explicit LgsBreakStmt() {}
    void createIRStmt(LgsCodeGen* codeGen) override;
    ~LgsBreakStmt() override = default;
};



