#include "cli/commands/LgsCompileCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"

void LgsCompileCmd::run() {
    LgsApp app;
    std::vector<const char*> args;
    parseArgs(app, args);
    app.compile();
}

LgsCliCmdHelp& LgsCompileCmd::getHelp() {
    return compileCmdHelp;
}
