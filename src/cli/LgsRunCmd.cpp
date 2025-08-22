#include "cli/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"
#include "types/LgsStr.h"

void LgsRunCmd::run() {
    const std::string subCmd = argv[2];
    if (subCmd[0] == '-') return exitWithError(unknownCmd + ": " + subCmd + ".");
    if (!fs::exists(subCmd)) return exitWithError("Path not found");
    LgsApp app(subCmd);

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] != '-' || arg.length() <= 1) {
            app.appArgs.emplace_back(arg.data());
            continue;
        }
        const char flag = arg[1];
        std::string value;
        if (arg.length() > 2) {
            value = arg.substr(2);
        } else if (i + 1 < argc && argv[i + 1][0] != '-') {
            value = argv[i + 1];
            i++;
        }

        switch (flag) {
        case 'o':
            app.configs.optLevel = value.empty() ? 0 : std::stoi(value);
            break;
        default:
            return exitWithError("Unknown flag: -" + std::string(1, flag));
        }
    }
    app.run();
}

std::string LgsRunCmd::joinArgs() const {
    std::ostringstream oss;
    for (int i = 2; i < argc; ++i) {
        if (i > 2) oss << ' ';
        oss << argv[i];
    }
    return oss.str();
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}