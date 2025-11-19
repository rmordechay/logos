#include "cli/commands/LgsAstCmd.h"
#include "errors/LgsCliErrors.h"
#include "tools/LgsJsonParser.h"
#include <iostream>

struct LgsCliCmdHelp;

void LgsAstCmd::run() {
    if (argc != 3) {
        return errHandler.addError(E40001);
    }
    const auto path = argv[2];
    if (!fs::exists(path)) {
        return errHandler.addError(E40004, {path});
    }
    if (!isLogosFile(path)) {
        return errHandler.addError(E40003, {path});
    }
    LgsApp app(path);
    if (!app.setup()) return;
    LgsFileMetadata metadata(path, 0);
    app.loadSrcFile(metadata);
    LgsJsonParser parser;
    parser.parseFile(app.srcFiles.front());
    std::cout << parser.json.str();
}

LgsCliCmdHelp& LgsAstCmd::getHelp() {
    return astCmdHelp;
}
