#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsDeferStmt final : public LgsStmt {
public:
    int index = -1;
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;

    void createIRStmt(LgsCodeGen* codeGen) override;
    void generateIR(LgsCodeGen* codeGen) const;
    ~LgsDeferStmt() override;
};
