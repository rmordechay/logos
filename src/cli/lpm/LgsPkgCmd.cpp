#include "cli/lpm/LgsPkgCmd.h"
#include "data/LgsCliErrors.h"
#include "cli/LgsCli.h"
#include "cli/lpm/LgsInstallCmd.h"

bool LgsPkgCmd::run() {
    const std::string subcmd = argv[2];
    if (subcmd == lgsHelpCmdHelp.name) {
        printHelp();
        return false;
    }
    LgsCliCmd* cmd = nullptr;
    if (subcmd == pkgInstallCmdHelp.name) {
        cmd = new LgsInstallCmd(argc, argv);
    } else {
        logError(E40000.msg);
        printParentCmdHelp(LPM_COMMANDS);
        return false;
    }
    const auto isHelp = argc == 4 && std::string(argv[3]) == lgsHelpCmdHelp.name;
    if (isHelp) cmd->printHelp();
    else cmd->run();
    delete cmd;
    return true;
}

LgsCliCmdHelp& LgsPkgCmd::getHelp() {
    return pkgCmdHelp;
}

void LgsPkgCmd::printHelp() {
    printParentCmdHelp(LPM_COMMANDS, pkgCmdHelp.name);
}
