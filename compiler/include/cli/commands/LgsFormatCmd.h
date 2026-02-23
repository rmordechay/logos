#pragma once
#include <string>

#include "cli/LgsCliCmd.h"
#include "cli/LgsCliHelp.h"

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
    .examples = {
        "lgs format path/to/root",
        "lgs format app.lgs",
    }
};
