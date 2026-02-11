#include "cli/commands/LgsFormatCmd.h"
#include "errors/LgsCliErrors.h"
#include "tools/LgsFormatter.h"

void LgsFormatCmd::run() {
    if (argc != 3) {
        return errHandler.addError(E40001, {});
    }
    fs::path path = argv[2];
    if (!fs::exists(path)) {
        return errHandler.addError(E40004, {path});
    }
    if (!isLogosFile(path)) {
        return errHandler.addError(E40003, {path});
    }
    LgsApp app(path);
    if (!app.setup()) return;
    app.loadSrcFile(&path);
    LgsFormatter formatter;
    formatter.formatFile(app.srcFiles.front());
}

LgsCliCmdHelp& LgsFormatCmd::getHelp() {
    return formatCmdHelp;
}
