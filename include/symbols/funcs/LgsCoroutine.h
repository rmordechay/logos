#pragma once
#include "LgsFunc.h"

class LgsCoroutine final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;

    void createIRValue(LgsCodeGen* codeGen) override;
    json::value_ref asJSON() override;
    ~LgsCoroutine() override;
};
