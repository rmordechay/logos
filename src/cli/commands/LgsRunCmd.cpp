#include "cli/commands/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "data/LgsCliErrors.h"
#include "logos/LgsApp.h"

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
    execute(execPath, args);
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
            const auto optLevel = parseInt(i, name);
            if (optLevel < 0) exitWithError(E40002, {"-o"});
            else if (optLevel > 3) exitWithError(E40003, {std::to_string(optLevel)});
            app.configs.optLevel = optLevel;
        }
        if (name[0] == 'c') {
            const auto code = argv[++i];
            argStart = i;
            app.lgsCode[LGS_MAIN_FILE] = code;
            return;
        }
    }
    if (argStart < 0) exitWithError(E40001);
    if (argStart >= argc) return;
    assert(fs::exists(argv[argStart]));
    app.paths.rootPath = fs::canonical(argv[argStart++]);
    for (int j = argStart; j < argc; ++j) {
        const auto v = argv[j];
        appArgs.push_back(v);
    }
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}
