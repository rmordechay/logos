#include "cli/commands/LgsCompileCmd.h"

#include <filesystem>

#include "logos/LgsApp.h"
#include "LgsUtils.h"
#include "errors/LgsErrHandler.h"
#include "files/LgsFile.h"

void LgsCompileCmd::run() {
    LgsApp app;
    std::vector<const char*> args;
    parseCompileArgs(app, args);
    if (!errHandler.successful) return;
    if (!app.compile()) {
        errHandler.mergeErrors(app.errHandler);
    }
    logInfo(app.srcFiles.front()->path);
}

LgsCliCmdHelp& LgsCompileCmd::getHelp() {
    return compileCmdHelp;
}
