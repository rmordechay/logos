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
    app.parseSrcFile(code, absFilePath);
    app.analyse();
    json::object ast;
    ast["ast"] = app.ast.front()->asJSON();
    if (withErrors) {
        ast["errors"] = app.errHandler.asJSON();
    }
    std::cout << ast["ast"];
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
