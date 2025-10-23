#include "cli/commands/LgsFormatCmd.h"

#include "data/LgsCliErrors.h"
#include "parser/LgsFormatter.h"

void LgsFormatCmd::run() {
    if (argc != 3) exitWithError(E40001);
    const auto path = argv[2];
    if (!fs::exists(path)) exitWithError(E40004, {path});
    if (!isLogosFile(path)) exitWithError(E40003, {path});
    LgsApp app;
    app.paths.rootPath = path;
    if (!app.setup()) app.errHandler.exitWithErrors();
    const LgsFileMetadata metadata(1, path);
    const auto code = getFileText(metadata.filePath);
    app.loadSrcFile(code, metadata.filePath, metadata.id);
    LgsFormatter formatter;
    formatter.formatFile(app.srcFiles.front());
}

LgsCliCmdHelp& LgsFormatCmd::getHelp() {
    return formatCmdHelp;
}
