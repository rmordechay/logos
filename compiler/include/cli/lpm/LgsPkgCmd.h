#pragma once
#include <string>
#include <vector>

#include "LgsInstallCmd.h"
#include "cli/LgsCliCmd.h"
#include "cli/LgsCliHelp.h"

class LgsPkgCmd final : public LgsCliCmd {
public:
    LgsPkgCmd(const int argc, char** argv): LgsCliCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
    void printHelp() override;
};

inline std::vector LPM_COMMANDS = {
    &pkgInstallCmdHelp,
};

inline LgsCliCmdHelp pkgCmdHelp{
    .name = "lpm",
    .usage = "lgs lpm <command> <options>",
    .summary = "Logos Package Manager.",
    .desc = "interact with the Logos Package Manager.",
    .examples = {
        "lgs lpm install",
        "lgs lpm install path/to/root",
        "lgs lpm install path/to/app.lgs",
    }
};
