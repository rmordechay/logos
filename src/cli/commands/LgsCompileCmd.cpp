#include "cli/commands/LgsCompileCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"

bool LgsCompileCmd::run() {
    LgsApp app;
    std::vector<const char*> args;
    parse(app, args);
    if (!errHandler.successful) return false;
    if (!app.compile()) {
        app.printErrors();
        return false;
    }
    logInfo(app.srcFiles.front()->path);
    return true;
}

LgsCliCmdHelp& LgsCompileCmd::getHelp() {
    return compileCmdHelp;
}
