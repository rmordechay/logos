#include "cli/LgsRunCmd.h"
#include "cli/LgsCliHelp.h"
#include "logos/LgsApp.h"
#include "types/LgsStr.h"

void LgsRunCmd::run() {
    const std::string subCmd = argv[2];
    if (subCmd[0] == '-') return exitWithError(unknownCmd + ": " + subCmd + ".");
    if (!fs::exists(subCmd)) return exitWithError("Path not found");
    LgsApp app(subCmd);
    if (argc > 3) {
        const std::string arg = argv[3];
        std::vector<char*> args;
        for (int i = 0; i < argc; ++i) {
            app.appArgs.emplace_back(argv[i]);
        }
    }
    app.run();
}

LgsCliCmdHelp& LgsRunCmd::getHelp() {
    return runCmdHelp;
}