#include "cli/LgsCli.h"
#include "cli/commands/LgsAstCmd.h"
#include "cli/commands/LgsFormatCmd.h"
#include "cli/commands/LgsGenerateCmd.h"
#include "cli/commands/LgsLinterCmd.h"
#include "cli/commands/LgsRunCmd.h"
#include "cli/commands/LgsTestCmd.h"
#include "data/LgsCliErrors.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"

void printLgsHelp();

inline LgsCliCmdHelp versionCmdHelp{
    .name = "version",
    .usage = "lgs version",
    .summary = "Prints Logos version.",
    .desc = "The version command prints the version of the current lgs binary.",
    .examples = {
        "lgs version",
    }
};

inline LgsCliCmdHelp helpCmdHelp{
    .name = "help",
    .usage = "lgs help",
    .summary = "Prints Logos help.",
    .desc = "The help command prints the main help of for lgs.",
    .examples = {
        "lgs help",
    }
};

void LgsCli::execute() const {
    if (argc < 2) exitWithError(E40001);
    const std::string cmdStr = argv[1];
    if (cmdStr == runCmdHelp.name) {
        LgsRunCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (cmdStr == testCmdHelp.name) {
        LgsTestCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (cmdStr == astCmdHelp.name) {
        LgsAstCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (cmdStr == linterCmdHelp.name) {
        LgsLinterCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (cmdStr == formatCmdHelp.name) {
        LgsFormatCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (cmdStr == generateCmdHelp.name) {
        LgsGenerateCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (cmdStr == helpCmdHelp.name) {
        printLgsHelp();
    } else if (cmdStr == versionCmdHelp.name) {
        logInfo(std::string(LOGOS_VERSION));
    } else {
        logError(E40000.msg);
        printLgsHelp();
    }
}

void LgsCli::runCmd(LgsCliCmd& cmd) const {
    const auto isHelp = argc == 3 && std::string(argv[2]) == helpCmdHelp.name;
    if (isHelp) cmd.printHelp();
    else cmd.run();
}

void printLgsHelp() {
    const std::string commands[][2] = {
        {runCmdHelp.name, runCmdHelp.summary},
        {testCmdHelp.name, testCmdHelp.summary},
        {astCmdHelp.name, astCmdHelp.summary},
        {formatCmdHelp.name, formatCmdHelp.summary},
        {linterCmdHelp.name, linterCmdHelp.summary},
        {versionCmdHelp.name, versionCmdHelp.summary},
        {helpCmdHelp.name, helpCmdHelp.summary},
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