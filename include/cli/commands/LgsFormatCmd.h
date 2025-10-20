#pragma once
#include "cli/LgsCliCmd.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsBool.h"

class LgsFormatCmd final : public LgsCliCmd {
public:
    LgsFormatCmd(const int argc, char** argv): LgsCliCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp formatCmdHelp{
    .name = "format",
    .usage = "lgs format <path> <options>",
    .summary = "Formats Logos code.",
    .desc = "The format command formats all the files in the project or a single file.",
    .optionalArgs = {
        {
            .name = "-p",
            .type = LgsBool::name,
            .defaultVal = "false",
            .possibleValues = "",
            .desc = "Pretty print the JSON output."
        },
    },
    .examples = {
        "lgs format app.lgs",
        "lgs format app.lgs -p",
    }
};
