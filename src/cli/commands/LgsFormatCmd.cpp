#include "cli/commands/LgsFormatCmd.h"
#include "data/LgsCliErrors.h"
#include "parser/LgsFormatter.h"

bool LgsFormatCmd::run() {
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
    LgsFileMetadata metadata(app.getNextFileID(), path);
    app.loadSrcFile(metadata);
    LgsFormatter formatter;
    formatter.formatFile(app.srcFiles.front());
    return true;
}

LgsCliCmdHelp& LgsFormatCmd::getHelp() {
    return formatCmdHelp;
}
