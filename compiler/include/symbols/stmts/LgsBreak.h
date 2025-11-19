#pragma once
#include "LgsStmt.h"

class LgsForLoop;

class LgsBreak final : public LgsStmt {
public:
    bool isBreakIf;
    std::string tag;

};
