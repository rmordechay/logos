#include "cli/commands/LgsCompileCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"

void LgsCompileCmd::run() {
    LgsApp app;
    std::vector<const char*> args;
    parseArgs(app, args);
    if (!app.compile()) app.printErrors();
}

LgsCliCmdHelp& LgsCompileCmd::getHelp() {
    return compileCmdHelp;
}
