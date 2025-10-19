#pragma once
#include "../LgsCliCmd.h"
#include "types/iterables/LgsStr.h"

class LgsTestCmd final : public LgsCliCmd{
public:
    LgsTestCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp testCmdHelp{
    .name = "run",
    .usage = "lgs run <path> <options>",
    .summary = "Runs tests.",
    .desc = "The test command runs all the tests in a the project or a single test.",
    .requiredArgs = {
        {
            .name = "<path>",
            .type = LgsStr::name,
            .desc = "Path to file or application root.",
        },
    },
    .examples = {
        "lgs test path/to/root",
    }
};