#pragma once
#include "cli/LgsCliCmd.h"

class LgsFormatCmd final : public LgsCliCmd {
public:
    LgsFormatCmd(const int argc, char** argv): LgsCliCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};
