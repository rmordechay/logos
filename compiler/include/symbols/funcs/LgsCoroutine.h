#pragma once
#include "stmts/LgsStmt.h"
#include "LgsValue.h"

class LgsFuncCall;
class LgsSelection;

class LgsCoroutine final : public LgsStmt {
public:
    LgsFuncCall* funcCall = nullptr;
    LgsSelection* selection = nullptr;
    void setDebugValue(LgsCodeGen& cg) override;
    ~LgsCoroutine() override;
};
