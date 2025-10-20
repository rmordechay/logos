#include "cli/LgsCli.h"
#include "cli/commands/LgsAstCmd.h"
#include "cli/commands/LgsFormatCmd.h"
#include "cli/commands/LgsLinterCmd.h"
#include "cli/commands/LgsRunCmd.h"
#include "cli/commands/LgsTestCmd.h"
#include "data/LgsCliErrors.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"

void printLgsHelp();

void LgsCli::execute() const {
    if (argc < 2) exitWithError(E40001);
    const std::string cmdStr = argv[1];
    if (cmdStr == runCmdHelp.name) {
        LgsRunCmd cmd(argc, argv);
        cmd.run();
    } else if (cmdStr == testCmdHelp.name) {
        LgsTestCmd cmd(argc, argv);
        cmd.run();
    } else if (cmdStr == astCmdHelp.name) {
        LgsAstCmd cmd(argc, argv);
        cmd.run();
    } else if (cmdStr == formatCmdHelp.name) {
        LgsLinterCmd cmd(argc, argv);
        cmd.run();
    } else if (cmdStr == linterCmdHelp.name) {
        LgsFormatCmd cmd(argc, argv);
        cmd.run();
    } else if (cmdStr == "help") {
        printLgsHelp();
    } else if (cmdStr == "version") {
        logInfo(std::string(LOGOS_VERSION));
    } else {
        logError(E40000.msg);
        printLgsHelp();
    }
}

void printLgsHelp() {
    const std::string commands[][2] = {
        {runCmdHelp.name, runCmdHelp.summary},
        {testCmdHelp.name, testCmdHelp.summary},
        {astCmdHelp.name, astCmdHelp.summary},
        {formatCmdHelp.name, formatCmdHelp.summary},
        {linterCmdHelp.name, linterCmdHelp.summary},
        {"version", "Prints Logos version."},
        {"help", "Prints Logos help."},
    };
    size_t maxLen = 0;
    std::ostringstream txt;
    for (auto& [name, desc] : commands) {
        maxLen = std::max(maxLen, name.size());
    }
    txt << LGS_COLORIZE("Help\n", LGS_MSG_COLOR_WHITE);
    txt << "Usage: " << "lgs <command> <options> <arguments>\n\n";
    txt << LGS_COLORIZE("Commands\n", LGS_MSG_COLOR_WHITE);
    for (auto& [name, desc] : commands) {
        txt << std::left << std::setw(maxLen + 4) << name << desc << '\n';
    }
    txt << "\nFor more information run 'lgs <command> help'.\n";
    logInfo(txt.str());
}
