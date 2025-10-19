#include "cli/commands/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"
#include "types/iterables/LgsStr.h"

void LgsRunCmd::run() {
    const std::string pathArg = argv[2];
    if (pathArg[0] == '-') return exitWithError(unknownCmd + ": " + pathArg + ".");
    if (!fs::exists(pathArg)) return exitWithError("Path not found");
    LgsApp app(pathArg);
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
