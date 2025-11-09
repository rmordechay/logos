#include "cli/commands/LgsAstCmd.h"
#include "data/LgsCliErrors.h"
#include "parser/LgsJsonParser.h"
#include <iostream>

struct LgsCliCmdHelp;

void LgsAstCmd::run() {
    if (argc != 3) exitWithError(E40001);
    const auto path = argv[2];
    if (!fs::exists(path)) exitWithError(E40004, {path});
    if (!isLogosFile(path)) exitWithError(E40003, {path});
    LgsApp app(path);
    if (!app.setup()) exitWithErrors(app.errHandler);
    LgsFileMetadata metadata(app.getNextFileID(), path, 0);
    app.loadSrcFile(metadata);
    LgsJsonParser parser;
    parser.parseFile(app.srcFiles.front());
    std::cout << parser.json.str();
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
