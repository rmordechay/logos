#include "cli/commands/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "data/LgsCliErrors.h"
#include "logos/LgsApp.h"
#include "types/iterables/LgsStr.h"

void LgsRunCmd::run() {
    LgsApp app;
    parseArgs(app);
    app.run();
}

void LgsRunCmd::parseArgs(LgsApp& app) const {
    if (argc < 3) exitWithError(E40001);
    auto argStart = -1;
    for (int i = 2; i < argc; ++i) {
        const auto arg = argv[i];
        if (arg[0] != '-') {
            argStart = i;
            break;
        }
        const auto name = std::string(arg).substr(1);
        if (name[0] == 'o') {
            const auto op = parseInt(i, name);
            if (op < 0) exitWithError(E40002, {"-o"});
            else if (op > 3) exitWithError(E40003, {std::to_string(op)});
            app.appConfigs.optLevel = op;
        }
    }

    if (argStart < 0) exitWithError(E40001);
    for (int j = argStart; j < argc; ++j) {
        const auto v = argv[j];
        app.mainArgs.push_back(v);
    }
    if (app.mainArgs.size() == 0) exitWithError(E40001);

    app.paths.rootPath = fs::absolute(app.mainArgs.front());
    app.mainArgs.erase(app.mainArgs.begin());
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}
