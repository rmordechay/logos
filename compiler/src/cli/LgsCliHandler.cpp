#include "cli/LgsCliHandler.h"

#include "cli/commands/LgsAstCmd.h"
#include "cli/commands/LgsCompileCmd.h"
#include "cli/commands/LgsFormatCmd.h"
#include "cli/commands/LgsGenerateCmd.h"
#include "cli/commands/LgsLinterCmd.h"
#include "cli/lpm/LgsPkgCmd.h"
#include "cli/commands/LgsRunCmd.h"
#include "cli/commands/LgsTestCmd.h"
#include "errors/LgsCliErrors.h"
#include "LgsUtils.h"
#include "cli/LgsCliCmd.h"
#include "errors/LgsErrHandler.h"
#include "errors/LgsErrors.h"

static std::vector COMMANDS = {
    &runCmdHelp,
    &compileCmdHelp,
    &pkgCmdHelp,
    &testCmdHelp,
    &astCmdHelp,
    &formatCmdHelp,
    &linterCmdHelp,
    &lgsVersionCmdHelp,
    &lgsHelpCmdHelp,
};

bool LgsCliHandler::execute() const {
    if (argc < 2) {
        printCliError(E40001);
        printParentCmdHelp(COMMANDS);
        return false;
    }
    const std::string cmdStr = argv[1];
    if (isHelpCommand(cmdStr)) {
        printParentCmdHelp(COMMANDS);
        return true;
    }
    if (isVersionCommand(cmdStr)) {
        logInfo("Logos " + std::string(LOGOS_VERSION) + '\n');
        return true;
    }
    const auto cmd = getCmd();
    if (!cmd) {
        logError(E40000.msg);
        printParentCmdHelp(COMMANDS);
        return false;
    }

    const auto isHelp = argc == 3 && isHelpCommand(argv[2]);
    if (isHelp) {
        cmd->printHelp();
    } else {
        cmd->run();
    }
    const auto successful = cmd->errHandler.successful;
    if (!successful) {
        cmd->errHandler.printErrors();
    }
    delete cmd;
    return successful;
}

LgsCliCmd* LgsCliHandler::getCmd() const {
    const std::string cmdStr = argv[1];
    if (cmdStr == compileCmdHelp.name) {
        return new LgsCompileCmd(argc, argv);
    }
    if (cmdStr == runCmdHelp.name) {
        return new LgsRunCmd(argc, argv);
    }
    if (cmdStr == testCmdHelp.name) {
        return new LgsTestCmd(argc, argv);
    }
    if (cmdStr == pkgCmdHelp.name) {
        return new LgsPkgCmd(argc, argv);
    }
    if (cmdStr == astCmdHelp.name) {
        return new LgsAstCmd(argc, argv);
    }
    if (cmdStr == linterCmdHelp.name) {
        return new LgsLinterCmd(argc, argv);
    }
    if (cmdStr == formatCmdHelp.name) {
        return new LgsFormatCmd(argc, argv);
    }
    if (cmdStr == generateCmdHelp.name) {
        return new LgsGenerateCmd(argc, argv);
    }
    return nullptr;
}
