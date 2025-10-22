#pragma once
#include "cli/LgsCliCmd.h"
#include "types/iterables/LgsStr.h"

class LgsGenerateCmd final : public LgsCliCmd {
public:
    LgsGenerateCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp generateCmdHelp{
    .name = "generate",
    .usage = "lgs generate <name>",
    .summary = "Generates Logos project.",
    .desc = "The generate command generates an empty Logos project.\nThe project will be generated in the same "
            "directory where the command is called and will be wrapped in a directory with the named project.",
    .requiredArgs = {
        {
            .name = "<name>",
            .type = LgsStr::name,
            .desc = "The name of the new project.",
        },
    },
    .examples = {
        "lgs generate project-name",
    }
};