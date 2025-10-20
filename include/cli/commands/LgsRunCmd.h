#pragma once
#include "cli/LgsCliCmd.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsRunCmd final : public LgsCliCmd {
public:
    LgsRunCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void parseArgs(LgsApp& app) const;
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp runCmdHelp{
    .name = "run",
    .usage = "lgs run <path> <options>",
    .summary = "Runs Logos code.",
    .desc = "The run command runs a Logos project or a single file.",
    .requiredArgs = {
        {
            .name = "<path>",
            .type = LgsStr::name,
            .desc = "Path to file or project root.",
        },
    },
    .optionalArgs = {
        {
            .name = "-o",
            .type = LgsInt::name,
            .defaultVal = "2",
            .possibleValues = "[0, 1, 2, 3]",
            .desc = "Optimization level."
        },
    },
    .examples = {
        "lgs run path/to/root",
        "lgs run app.lgs",
        "lgs run app.lgs -o3",
    }
};
