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
            .desc = "Path to file or application root",
            .required = true
        },
    },
    .opts = {
        {
            .name = "-o",
            .type = LgsInt::name,
            .defaultVal = "2",
            .possibleValues = "[0, 1, 2, 3]",
            .desc = "Optimization level\0"
        },
    }
};

void LgsRunCmd::run() {
    if (argc < 3) {
        errMsg = "Too few arguments for command 'run'.";
        return;
    }
    const std::string subCmd = argv[2];
    if (subCmd == "help") {
        return printHelp();
    }
    if (argv[2][0] == '-') return logError(unknownCmd);
    if (!fs::exists(argv[2])) return logError("Path not found");
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
    if (argc == 3) {
        if (std::strcmp(argv[2], "help") != 0) {
            printHelp();
            return true;
        }
    }
    if (argv[2][0] == '-') return false;
    return fs::exists(argv[2]);
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}
