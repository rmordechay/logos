#pragma once
#include "LgsStmt.h"

class LgsStmtsBlock;

class LgsDeferStmt final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;

    void createIRValue(LgsCodeGen* codeGen) override;
    json::object asJSON() override;
    void generateIR(LgsCodeGen* codeGen) const;
    ~LgsDeferStmt() override;
};
