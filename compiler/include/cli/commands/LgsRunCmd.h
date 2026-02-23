#pragma once
#include <string>
#include <vector>

#include "cli/LgsCliCmd.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsBool.h"
#include "types/primitives/LgsInt.h"
#include "cli/LgsCliHelp.h"

class LgsApp;

class LgsRunCmd : public LgsCliCmd {
public:
    LgsRunCmd(const int argc, char** argv) : LgsCliCmd(argc, argv) {}
    void parseCompileArgs(LgsApp& app, std::vector<const char*>& appArgs);
    void run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline std::vector<LgsCliCmdArgHelp> runCompileOptionalArgs = {
    {
        .name = "-o",
        .name2 = "--optimize",
        .type = LgsInt::name,
        .defaultVal = "2",
        .possibleValues = "[0, 1, 2, 3]",
        .desc = "Optimization level."
    },
    {
        .name = "-c",
        .name2 = "--code",
        .type = LgsBool::name,
        .defaultVal = "false",
        .desc = "Code mode. Run Logos code by passing code directly."
    },
    {
        .name = "-d",
        .name2 = "--debug",
        .type = LgsBool::name,
        .defaultVal = "false",
        .desc = "Run Logos code in debug mode."
    },
};

inline LgsCliCmdHelp runCmdHelp{
    .name = "run",
    .usage = "lgs run <options> <path/code>",
    .summary = "Runs Logos code.",
    .desc = "The run command runs a Logos project or a single file.",
    .requiredArgs = {
        {
            .name = "<path>",
            .type = LgsStr::name,
            .desc = "Path to file or project root.",
        },
    },
    .optionalArgs = runCompileOptionalArgs,
    .examples = {
        "lgs run app.lgs",
        "lgs run path/to/root",
        "lgs run app.lgs -o3",
        "lgs run -c \"main() { print('Hello world') }\"",
    }
};
