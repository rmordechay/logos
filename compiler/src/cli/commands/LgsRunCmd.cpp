#include "cli/commands/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "errors/LgsCliErrors.h"
#include "logos/LgsApp.h"

void LgsRunCmd::run() {
    fs::path execPath = "";
    std::vector<const char*> args;
    {
        LgsApp app;
        parseCompileArgs(app, args);
        if (!errHandler.successful) return;
        if (!app.compile()) {
            errHandler.mergeErrors(app.errHandler);
            return;
        }
        execPath = app.paths.execFile;
    }
    assert(execPath != "");
    execute(execPath, args);
}

void LgsRunCmd::parseCompileArgs(LgsApp& app, std::vector<const char*>& appArgs) {
    if (argc < 3) return errHandler.addError(E40001);
    auto argStart = parseArgs(2, [this, &app](const std::string& cmd, int& i) {
        if (isArgEqual(cmd, {"o", "optimize"})) {
            int optLevel;
            if (cmd.size() == 1) optLevel = argv[++i][0] - '0';
            else if (cmd.size() == 2) optLevel = cmd[1] - '0';
            else return errHandler.addError(E40002, {"-o"});
            if (optLevel > 3) return errHandler.addError(E40003, {std::to_string(optLevel)});
            app.configs.optLevel = optLevel;
        } else if (isArgEqual(cmd, {"c", "code"})) {
            app.configs.appMode = FILE_MODE;
        } else if (isArgEqual(cmd, {"d", "debug"})) {
            app.configs.debugMode = true;
        } else {
            errHandler.addError(E40003, {cmd});
        }
    });

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
