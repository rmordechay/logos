#include "cli/lpm/LgsPkgCmd.h"
#include "data/LgsCliErrors.h"
#include "cli/LgsCliHandler.h"
#include "cli/lpm/LgsInstallCmd.h"

void LgsPkgCmd::run() {
    const std::string subcmd = argv[2];
    if (isHelpCommand(subcmd)) {
        return printHelp();
    }
    LgsCliCmd* cmd = nullptr;
    if (subcmd == pkgInstallCmdHelp.name) {
        cmd = new LgsInstallCmd(argc, argv);
    } else {
        logError(E40000.msg);
        return printParentCmdHelp(LPM_COMMANDS);
    }
    const auto isHelp = argc == 4 && std::string(argv[3]) == lgsHelpCmdHelp.name;
    if (isHelp) cmd->printHelp();
    else cmd->run();
    if (!cmd->errHandler.successful) cmd->errHandler.printErrors();
    delete cmd;
}

LgsCliCmdHelp& LgsPkgCmd::getHelp() {
    return pkgCmdHelp;
}

void LgsPkgCmd::printHelp() {
    printParentCmdHelp(LPM_COMMANDS, pkgCmdHelp.name);
}
