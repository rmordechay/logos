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
        if (!app.compile()) return app.printErrors();
        execPath = app.appPaths.execFile;
    }
    assert(execPath != "");
    execute(execPath, args);
}

void LgsRunCmd::parseArgs(LgsApp& app, std::vector<const char*>& appArgs) const {
    if (argc < 3) return printCliError(E40001);
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
            if (optLevel < 0) return printCliError(E40002, {"-o"});
            else if (optLevel > 3) return printCliError(E40003, {std::to_string(optLevel)});
            app.configs.optLevel = optLevel;
        }
        if (name[0] == 'c') {
            const auto code = argv[++i];
            app.lgsCode[LGS_MAIN_FILE] = code;
            app.configs.appMode = FILE_MODE;
            return;
        }
    }
    if (argStart < 0) return printCliError(E40001);
    if (argStart >= argc) return;
    auto path = argv[argStart++];
    if (!fs::exists(path)) return printCliError(E40004, {path});
    app.appPaths.rootPath = path;
    for (int j = argStart; j < argc; ++j) {
        const auto v = argv[j];
        appArgs.push_back(v);
    }
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}
