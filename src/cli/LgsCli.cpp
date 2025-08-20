#include "cli/LgsCli.h"
#include "cli/LgsRunCmd.h"
#include "configs/LgsDefinitions.h"
#include "utils/LgsUtils.h"

void LgsCli::execute() const {
    if (argc < 2) {
        logError("not enough arguments. See usage:\n\n");
        printLgsHelp();
        exit(0);
    }

    const std::string cmdStr = argv[1];
    if (cmdStr == "run") {
        LgsRunCmd cmd(argc, argv);
        cmd.run();
    } else if (cmdStr == "ast") {
        LgsRunCmd cmd(argc, argv);
        cmd.run();
    } else if (cmdStr == "help") {
        printLgsHelp();
    } else if (cmdStr == "version" || cmdStr == "-v" || cmdStr == "--version") {
        logInfo(std::string(LOGOS_VERSION));
    }
}

void printLgsHelp() {
    const std::string commands[][2] = {
        {"run", "Executes Logos script or application."},
        {"version, -v, --version", "Prints Logos version."},
        {"help, --help", "Prints Logos help."},
    };
    size_t maxLen = 0;
    std::ostringstream txt;
    for (auto& [name, desc] : commands) {
        maxLen = std::max(maxLen, name.size());
    }
    txt << LGS_COLORIZE("Help\n", LGS_MSG_COLOR_WHITE);
    txt << "Usage: " << "lgs <command> <options>\n\n";
    txt << LGS_COLORIZE("Commands\n", LGS_MSG_COLOR_WHITE);
    for (auto& [name, desc] : commands) {
        txt << std::left << std::setw(maxLen + 4) << name << desc << '\n';
    }
    txt << "\nFor more information: lgs <command> help\n";
    logInfo(txt.str());
}
