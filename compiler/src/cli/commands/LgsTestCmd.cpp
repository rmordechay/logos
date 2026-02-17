#include "cli/commands/LgsTestCmd.h"

void LgsTestCmd::run() {
    fs::path execPath = "";
    std::vector<const char*> args;
    {
        LgsApp app;
        app.configs.isTestRun = true;
        parseCompileArgs(app, args);
        if (!errHandler.successful) return;
        if (!app.compile()) {
            errHandler.mergeErrors(app.errHandler);
            return;
        }
        execPath = app.paths.testExecFile;
    }
    assert(execPath != "");
    execute(execPath, args);
}

LgsCliCmdHelp& LgsTestCmd::getHelp() {
    return testCmdHelp;
}
