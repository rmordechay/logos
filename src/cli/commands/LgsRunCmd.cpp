#include "cli/commands/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "data/LgsCliErrors.h"
#include "logos/LgsApp.h"
#include "types/iterables/LgsStr.h"

void LgsRunCmd::run() {
    fs::path execPath = "";
    std::vector<const char*> args;
    {
        LgsApp app;
        parseArgs(app, args);
        app.compile();
        execPath = app.paths.execFilePath;
    }
    assert(execPath != "");
    execute(args, execPath);
}

void LgsRunCmd::parseArgs(LgsApp& app, std::vector<const char*>& appArgs) const {
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
    if (argStart >= argc) return;
    app.paths.rootPath = fs::absolute(argv[argStart++]);
    for (int j = argStart; j < argc; ++j) {
        const auto v = argv[j];
        appArgs.push_back(v);
    }
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}
