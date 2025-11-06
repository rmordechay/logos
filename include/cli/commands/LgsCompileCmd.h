#pragma once
#include "LgsRunCmd.h"
#include "cli/LgsCliCmd.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsCompileCmd final : public LgsRunCmd {
public:
    LgsCompileCmd(const int argc, char** argv) : LgsRunCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp compileCmdHelp{
    .name = "compile",
    .usage = "lgs compile <path> <options>",
    .summary = "Compiles Logos code.",
    .desc = "The compile command compiles a Logos project or a single file.",
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
        "lgs compile path/to/root",
        "lgs compile app.lgs",
        "lgs compile app.lgs -o3",
    }
};
