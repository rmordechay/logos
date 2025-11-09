#include "cli/commands/LgsFormatCmd.h"
#include "data/LgsCliErrors.h"
#include "parser/LgsFormatter.h"

void LgsFormatCmd::run() {
    if (argc != 3) return printCliError(E40001);
    const auto path = argv[2];
    if (!fs::exists(path)) return printCliError(E40004, {path});
    if (!isLogosFile(path)) return printCliError(E40003, {path});
    LgsApp app(path);
    if (!app.setup()) return app.printErrors();
    LgsFileMetadata metadata(app.getNextFileID(), path);
    app.loadSrcFile(metadata);
    LgsFormatter formatter;
    formatter.formatFile(app.srcFiles.front());
}

LgsCliCmdHelp& LgsFormatCmd::getHelp() {
    return formatCmdHelp;
}
