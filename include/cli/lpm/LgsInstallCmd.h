#pragma once
#include "cli/LgsCliCmd.h"
#include "logos/LgsPkgManager.h"

class LgsInstallCmd final : public LgsCliCmd {
public:
    LgsPkgManager pkgManager;

    LgsInstallCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    bool run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp pkgInstallCmdHelp{
    .name = "install",
    .usage = "lgs pkg install <options> <path>",
    .summary = "Install Logos package.",
    .desc = "installs Logos packages.",
    .examples = {
        "lgs pkg install github/user/repo:1.0.0",
    }
};
