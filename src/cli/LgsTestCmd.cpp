#include "cli/LgsTestCmd.h"

void LgsTestCmd::run() {
    const std::string pathArg = argv[2];
    if (pathArg[0] == '-') return exitWithError(unknownCmd + ": " + pathArg + ".");
    if (!fs::exists(pathArg)) return exitWithError("Path not found");
    LgsApp app(pathArg);
    app.appConfigs.isTestRun = true;
    app.runTests();
}

LgsCliCmdHelp& LgsTestCmd::getHelp() {
    return testCmdHelp;
}
