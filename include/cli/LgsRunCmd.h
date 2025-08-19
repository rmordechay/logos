#pragma once
#include "LgsCliCmd.h"

class LgsRunCmd final : public LgsCliCmd {
public:
    LgsRunCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void run() override;
    bool setup() override;
    LgsCliCmdHelp& help() override;
};
