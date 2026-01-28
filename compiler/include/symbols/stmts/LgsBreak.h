#pragma once
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreak final : public LgsStmt {
public:
    bool isBreakIf = false;
    std::string tag = "";
    void setDebugValue(LgsCodeGen& cg) override;
};
