#pragma once
#include "stmts/LgsStmt.h"

class LgsCoroutine final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsCoroutine() override;
};
