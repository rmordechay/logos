#pragma once
#include "LgsStmt.h"
#include "LgsValue.h"

class LgsContinue final : public LgsStmt {
public:
    LgsForLoop* forLoop = nullptr;
    void setDebugValue(LgsCodeGen& cg) override;
};



