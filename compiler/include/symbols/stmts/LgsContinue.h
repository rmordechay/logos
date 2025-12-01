#pragma once
#include "LgsStmt.h"

class LgsContinue final : public LgsStmt {
public:
    void setDebugValue(LgsCgModule& cg) override;
};



