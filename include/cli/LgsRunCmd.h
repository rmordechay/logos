#pragma once
#include "LgsCliCmd.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsRunCmd final : public LgsCliCmd {
public:
    LgsRunCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void run() override;
    std::string joinArgs() const;
    LgsCliCmdHelp& getHelp() override;
    void setArg(const std::string& key, const std::string& value, LgsApp& app) override;
};

inline LgsCliCmdHelp runCmdHelp{
    .name = "run",
    .usage = "lgs run <path> <options>",
    .summary = "Runs a Logos application or a single file.",
    .desc = "The run command runs a Logos application or a single file.",
    .requiredArgs = {
        {
            .name = "<path>",
            .type = LgsStr::name,
            .desc = "Path to file or application root.",
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
