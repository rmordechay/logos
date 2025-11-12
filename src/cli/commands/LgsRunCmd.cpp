#include "cli/commands/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "data/LgsCliErrors.h"
#include "logos/LgsApp.h"

bool LgsRunCmd::run() {
    fs::path execPath = "";
    std::vector<const char*> args;
    {
        LgsApp app;
        parse(app, args);
        if (!errHandler.successful) return false;
        if (!app.compile()) {
            app.printErrors();
            return false;
        }
        execPath = app.paths.execFile;
    }
    assert(execPath != "");
    execute(execPath, args);
    return true;
}

void LgsRunCmd::parse(LgsApp& app, std::vector<const char*>& appArgs) {
    if (argc < 3) return errHandler.addError(E40001);
    auto f = [this, &app](const int i, const std::string& cmd) {
        const auto isSingleDash = cmd.size() == 1;
        if ((isSingleDash && cmd[0] == 'o') || cmd == "optimize") {
            const auto optLevel = parseIntArg(i, cmd);
            if (optLevel < 0) return errHandler.addError(E40002, {"-o"});
            if (optLevel > 3) return errHandler.addError(E40003, {std::to_string(optLevel)});
            app.configs.optLevel = optLevel;
        } else if ((isSingleDash && cmd[0] == 'c') || cmd == "code") {
            app.configs.appMode = FILE_MODE;
        } else if ((isSingleDash && cmd[0] == 'd') || cmd == "debug") {
            app.configs.debugMode = true;
        } else {
            errHandler.addError(E40003, {cmd});
        }
    };

    auto argStart = parseArgs(2, f);
    if (argStart < 0) return errHandler.addError(E40001);
    if (app.configs.appMode == FILE_MODE) {
        app.lgsCode[LGS_MAIN_FILE] = argv[argStart++];
    } else {
        auto path = argv[argStart++];
        if (!fs::exists(path)) return errHandler.addError(E40004, {path});
        app.paths.rootPath = path;
    }
    for (int i = argStart; i < argc; ++i) {
        const auto v = argv[i];
        appArgs.push_back(v);
    }
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}
