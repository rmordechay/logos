#pragma once
#include "LgsFunc.h"

class LgsCoroutine final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;
    void setDebugValue(LgsCgModule& cg) override;
    ~LgsCoroutine() override;
};
