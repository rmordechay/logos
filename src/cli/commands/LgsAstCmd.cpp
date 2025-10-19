#include "cli/commands/LgsAstCmd.h"
#include "files/LgsFile.h"

struct LgsCliCmdHelp;

void LgsAstCmd::run() {
    const std::string pathArg = argv[2];
    if (pathArg[0] == '-') return exitWithError(unknownCmd + ": " + pathArg + ".");
    if (!fs::exists(pathArg)) return exitWithError("Path not found");
    LgsApp app(pathArg);
    parseArguments(3, app);
    app.setup();
    const auto code = getFileText(pathArg);
    assert(code != "");
    app.loadSrcFile(code, pathArg);
    LgsJsonParser jsonParser;
    jsonParser.pretty = true;
    jsonParser.visitFile(app.srcFiles.front());
    std::cout << jsonParser.json.str();
}

void LgsAstCmd::setArg(const std::string& key, const std::string& value, LgsApp& app) {
    if (key == "-p" && value == "") {
        app.appConfigs.optLevel = std::stoi(value);
    }
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
