#pragma once
#include <string>

#include "LgsStmt.h"
#include "LgsValue.h"

class LgsForLoop;

class LgsBreak final : public LgsStmt {
public:
    bool isBreakIf = false;
    LgsIfStmt* ifStmt = nullptr;
    LgsForLoop* forLoop = nullptr;

    std::string tag = "";
    void setDebugValue(LgsCodeGen& cg) override;
};
