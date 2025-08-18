#pragma once
#include "LgsStmt.h"

class LgsContinue final : public LgsStmt {
public:
    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
};



