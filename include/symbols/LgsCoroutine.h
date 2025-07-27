#pragma once
#include "funcs/LgsFunc.h"

class LgsCoroutine final : public LgsStmt {
public:
    LgsStmtsBlock* stmtsBlock = nullptr;
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;

    void createIRStmt(LgsModule* module) override;
    ~LgsCoroutine() override = default;
};
