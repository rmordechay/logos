#pragma once
#include "LgsCliCmd.h"

class LgsTestCmd final : public LgsCliCmd{
public:
    LgsTestCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};
