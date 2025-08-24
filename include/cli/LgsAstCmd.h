#pragma once
#include "LgsCliCmd.h"
#include "types/LgsStr.h"

class LgsAstCmd final : public LgsCliCmd {
public:
    bool withErrors = false;

    LgsAstCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp astCmdHelp{
    .name = "ast",
    .usage = "lgs ast <file>",
    .summary = "Generates an AST from the source file.",
    .desc = "The ast command generates an AST from the source file.",
    .requiredArgs = {
        {
            .name = "<file>",
            .type = LgsStr::name,
            .desc = "Path to file.",
        }
    },
    .examples = {
        "lgs ast app.lgs",
        "lgs ast app.lgs --no-errors",
    }
};
