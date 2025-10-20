#include "cli/commands/LgsAstCmd.h"
#include "data/LgsCliErrors.h"
#include "files/LgsFile.h"

struct LgsCliCmdHelp;

void LgsAstCmd::run() {
    LgsApp app;
    if (argc != 3) exitWithError(E40001);
    const auto path = argv[2];
    if (!fs::exists(path)) exitWithError(E40004, {path});
    if (!isLogosFile(path)) exitWithError(E40005, {path});
    const auto code = getFileText(path);
    app.loadSrcFile(code, path);
    LgsJsonParser parser;
    parser.parseFile(app.srcFiles.front());
    std::cout << parser.json.str();
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
