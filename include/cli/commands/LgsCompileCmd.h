#pragma once
#include "LgsRunCmd.h"
#include "cli/LgsCliCmd.h"
#include "types/iterables/LgsStr.h"
#include "types/primitives/LgsInt.h"

class LgsCompileCmd final : public LgsRunCmd {
public:
    LgsCompileCmd(const int argc, char** argv) : LgsRunCmd(argc, argv) {}
    bool run() override;
    LgsCliCmdHelp& getHelp() override;
};

inline LgsCliCmdHelp compileCmdHelp{
    .name = "compile",
    .usage = "lgs compile <path> <options>",
    .summary = "Compiles Logos code.",
    .desc = "The compile command compiles a Logos project or a single file.\n"
            "In project mode, the complied files will be saved in the build directory.\n"
            "In file mode, the compiled file path will be printed after running the command.",
    .requiredArgs = {
        {
            .name = "<path>",
            .type = LgsStr::name,
            .desc = "Path to file or project root.",
        },
    },
    .optionalArgs = runCompileOptionalArgs,
    .examples = {
        "lgs compile path/to/root",
        "lgs compile app.lgs",
        "lgs compile app.lgs -o3",
    }
};
