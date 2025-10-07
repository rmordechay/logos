#include "cli/LgsAstCmd.h"
#include "files/LgsFile.h"

void LgsAstCmd::run() {
    const auto filePath = argv[2];
    if (!fs::exists(filePath)) {
        exitWithError("File '" + std::string(filePath) + "' was not found.");
    }
    LgsApp app(fs::canonical(filePath));
    app.setup();
    app.loadBuiltins();
    const auto absFilePath = fs::path(fs::canonical(filePath));
    const std::string code = getFileText(absFilePath);
    app.loadSrcFile(code, absFilePath);
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
