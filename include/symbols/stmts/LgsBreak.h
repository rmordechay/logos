#pragma once
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreak final : public LgsStmt {
public:
    std::string tag;
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
};



