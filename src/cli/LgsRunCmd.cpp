#include "cli/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"
#include "types/iterables/LgsStr.h"

void LgsRunCmd::run() {
    const std::string subCmd = argv[2];
    if (subCmd[0] == '-') return exitWithError(unknownCmd + ": " + subCmd + ".");
    if (!fs::exists(subCmd)) return exitWithError("Path not found");
    LgsApp app(subCmd);
    parseArguments(3, app);
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

void LgsRunCmd::setArg(const std::string& key, const std::string& value, LgsApp& app) {
    if (key == "o") {
        app.appConfigs.optLevel = std::stoi(value);
    }
}
