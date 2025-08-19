#include "cli/LgsRunCmd.h"
#include "logos/LgsApp.h"
#include "types/LgsStr.h"
#include "types/primitives/LgsInt.h"

inline LgsCliCmdHelp runCmdHelp{
    .name = "run",
    .usage = "lgs run <path> <options>",
    .args = {
        {
            .name = "<path>",
            .type = LgsStr::name,
            .desc = "Path to file or application root.",
            .required = true
        },
    },
    .opts = {
        {
            .name = "-o",
            .type = LgsInt::name,
            .defaultVal = "2",
            .possibleValues = "[0, 1, 2, 3]",
            .desc = "Optimization level"
        },
    }
};

void LgsRunCmd::run() {
    LgsApp app(argv[2]);
    std::vector<char*> args;
    for (int i = 0; i < argc; ++i) {
        app.appArgs.emplace_back(argv[i]);
    }
    app.run();
}

bool LgsRunCmd::setup() {
    if (argc < 3) {
        errMsg = "Too few arguments for command 'run'.";
        return false;
    }
    if (argv[2][0] == '-') return false;
    return fs::exists(argv[2]);
}

LgsCliCmdHelp& LgsRunCmd::help() {
    return runCmdHelp;
}
