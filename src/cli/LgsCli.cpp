#include "cli/LgsCli.h"
#include "cli/LgsAstCmd.h"
#include "cli/LgsRunCmd.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"

void printLgsHelp();

void LgsCli::execute() const {
    if (argc < 2) {
        logError("not enough arguments. See usage:\n\n");
        printLgsHelp();
        exit(0);
    }

    const std::string firstCmdStr = argv[1];
    if (firstCmdStr == "run") {
        LgsRunCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (firstCmdStr == "ast") {
        LgsAstCmd cmd(argc, argv);
        runCmd(cmd);
    } else if (firstCmdStr == "help") {
        printLgsHelp();
    } else if (firstCmdStr == "version" || firstCmdStr == "-v" || firstCmdStr == "--version") {
        logInfo(std::string(LOGOS_VERSION));
    } else {
        logError("Unknown command.\n" + cmdStr + "\n\n");
        printLgsHelp();
    }
}

void LgsCli::runCmd(LgsCliCmd& cmd) const {
    if (isHelpCmd()) return cmd.printHelp();
    const auto requiredArgs = cmd.getHelp().requiredArgs.size();
    if (argc - 2 < requiredArgs) {
        cmd.exitWithError("Too few arguments for command '%s" + cmd.getHelp().name + "'.");
    }
    cmd.run();
}

bool LgsCli::isHelpCmd() const {
    return argc > 2 && std::string(argv[2]) == "help";
}

void printLgsHelp() {
    const std::string commands[][2] = {
        {"run", runCmdHelp.summary},
        {"ast", astCmdHelp.summary},
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

void LgsCli::joinCmdStr() {
    std::ostringstream oss;
    for (int i = 0; i < argc; i++) {
        if (i > 0) oss << " ";
        if (i == 0) {
            std::string prog(argv[0]);
            const auto pos = prog.find_last_of("/\\");
            if (pos != std::string::npos) {
                prog = prog.substr(pos + 1);
            }
            oss << prog;
        } else {
            oss << argv[i];
        }
    }
    cmdStr = oss.str();
}
