#include "cli/commands/LgsTestCmd.h"

#include <assert.h>
#include <filesystem>

#include "LgsUtils.h"
#include "errors/LgsErrHandler.h"
#include "logos/LgsApp.h"
#include "logos/LgsAppConfigs.h"
#include "logos/LgsPaths.h"

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
        execPath = app.paths.execFile;
    }
    assert(execPath != "");
    execute(execPath, args);
}

LgsCliCmdHelp& LgsTestCmd::getHelp() {
    return testCmdHelp;
}
