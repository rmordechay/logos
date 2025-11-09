#pragma once
#include "cli/LgsCliCmd.h"
#include "types/iterables/LgsStr.h"

class LgsLinterCmd final : public LgsCliCmd {
public:
    LgsLinterCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    bool run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp linterCmdHelp{
    .name = "linter",
    .usage = "lgs linter <path> <options>",
    .summary = "Runs Logos linter.",
    .desc = "The linter command runs the Logos linter on the whole project or a single file.",
    .requiredArgs = {
        {
            .name = "<path>",
            .type = LgsStr::name,
            .desc = "Path to file or project root.",
        },
    },
    .examples = {
        "lgs linter path/to/root",
        "lgs linter app.lgs",
    }
};