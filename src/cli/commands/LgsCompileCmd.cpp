#include "cli/commands/LgsCompileCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"

bool LgsCompileCmd::run() {
    LgsApp app;
    std::vector<const char*> args;
    if (!parseArgs(app, args)) return false;
    if (!app.compile()) {
        app.printErrors();
        return false;
    }
    return true;
}

LgsCliCmdHelp& LgsCompileCmd::getHelp() {
    return compileCmdHelp;
}
