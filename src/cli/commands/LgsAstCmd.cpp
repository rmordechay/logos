#include "cli/commands/LgsAstCmd.h"
#include "data/LgsCliErrors.h"
#include "../../../include/tools/LgsJsonParser.h"
#include <iostream>

struct LgsCliCmdHelp;

bool LgsAstCmd::run() {
    if (argc != 3) {
        printCliError(E40001);
        return false;
    }
    const auto path = argv[2];
    if (!fs::exists(path)) {
        printCliError(E40004, {path});
        return false;
    }
    if (!isLogosFile(path)) {
        printCliError(E40003, {path});
        return false;
    }
    LgsApp app(path);
    if (!app.setup()) {
        app.printErrors();
        return false;
    }
    LgsFileMetadata metadata(app.getNextFileID(), path, 0);
    app.loadSrcFile(metadata);
    LgsJsonParser parser;
    parser.parseFile(app.srcFiles.front());
    std::cout << parser.json.str();
    return true;
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
