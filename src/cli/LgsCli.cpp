#include "cli/LgsCli.h"
#include "cli/LgsRunCmd.h"
#include "configs/LgsDefinitions.h"
#include "utils/LgsUtils.h"

void LgsCli::execute() const {
    if (argc < 2) {
        logInfo("Error: not enough arguments.\n\n");
        printLgsHelp();
        exit(0);
    }

    const std::string cmdStr = argv[1];
    if (cmdStr == "run") {
        LgsRunCmd command(argc, argv);
        runCmd(command);
    } else if (cmdStr == "ast") {
        LgsRunCmd command(argc, argv);
        runCmd(command);
    } else if (cmdStr == "help") {
        printLgsHelp();
    } else if (cmdStr == "version" || cmdStr == "-v" || cmdStr == "--version") {
        logInfo(std::string(LOGOS_VERSION));
    }
}

void LgsCli::runCmd(LgsCliCmd& cmd) const {
    if (!cmd.setup()) {
        std::ostringstream cmdStr;
        for (int i = 1; i < argc; ++i) {
            if (i > 1) cmdStr << " ";
            cmdStr << argv[i];
        }
        const auto errMsg = cmd.errMsg != "" ? cmd.errMsg : "Wrong command '" + cmdStr.str() + "'.";
        logInfo(LGS_ERROR_STR + errMsg + "\n\n");
        printHelp(cmd);
        exit(1);
    }
    if (cmd.argc == 3 && std::strcmp(cmd.argv[2], "help") != 0) {
        printHelp(cmd);
        return;
    }
    cmd.run();
}

size_t getPadding(const LgsCliCmdHelp& help) {
    size_t padding = 0;
    for (const auto& arg : help.args) {
        padding = std::max(padding, std::strlen(arg.name));
    }
    for (const auto& arg : help.opts) {
        padding = std::max(padding, std::strlen(arg.name));
    }
    if (padding < 6) padding = 6;
    return padding;
}

void LgsCli::printHelp(LgsCliCmd& cmd) {
    const auto help = cmd.help();
    std::ostringstream txt;
    txt << LGS_COLORIZE("Help", LGS_MSG_COLOR_WHITE) << '\n';
    const auto padding = getPadding(help);

    txt << std::left << std::setw(padding + 4) << "Usage:" << help.usage << "\n";
    // Required args
    if (!help.args.empty()) {
        txt << '\n' << LGS_COLORIZE("Required Arguments:", LGS_MSG_COLOR_WHITE) << '\n';
        for (const auto arg : help.args) {
            txt << std::left << std::setw(padding + 4);
            txt << arg.name << arg.desc << '\n';
        }
    }

    // Options
    if (!help.opts.empty()) {
        txt << '\n' << LGS_COLORIZE("Options:", LGS_MSG_COLOR_WHITE) << '\n';
        for (const auto arg : help.opts) {
            txt << std::left << std::setw(padding + 4);
            txt << arg.name << arg.desc << '\n';
        }
    }
    logInfo(txt.str());
}

void printLgsHelp() {
    const std::string commands[][2] = {
        {"run", "Executes a Logos script or run application"},
        {"help", "Prints this help"},
        {"version", "Prints Logos version"}
    };
    size_t maxLen = 0;
    std::ostringstream txt;
    for (auto& [name, desc] : commands) {
        maxLen = std::max(maxLen, name.size());
    }
    txt << std::left << std::setw(maxLen + 4) << "Usage:" << "lgs <command> <options>\n\n";
    txt << "Commands:\n";
    for (auto& [name, desc] : commands) {
        txt << std::left << std::setw(maxLen + 4) << name << desc << '\n';
    }
    txt << "\nFor more information: lgs [command] help\n";
    logInfo(txt.str());
}
