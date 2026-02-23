#pragma once
#include "LgsStmt.h"
#include "LgsValue.h"

class LgsContinue final : public LgsStmt {
public:
    void setDebugValue(LgsCodeGen& cg) override;
};



