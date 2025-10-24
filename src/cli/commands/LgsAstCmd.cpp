#include "cli/commands/LgsAstCmd.h"
#include "data/LgsCliErrors.h"
#include "parser/LgsJsonParser.h"

struct LgsCliCmdHelp;

void LgsAstCmd::run() {
    if (argc != 3) exitWithError(E40001);
    const auto path = argv[2];
    if (!fs::exists(path)) exitWithError(E40004, {path});
    if (!isLogosFile(path)) exitWithError(E40003, {path});
    LgsApp app;
    app.paths.rootPath = path;
    if (!app.setup()) app.errHandler.exitWithErrors();
    const LgsFileMetadata metadata(app.getNextFileID(), path);
    const auto code = getFileText(metadata.path);
    app.loadSrcFile(code, metadata.path, metadata.id);
    LgsJsonParser parser;
    parser.parseFile(app.srcFiles.front());
    std::cout << parser.json.str();
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
