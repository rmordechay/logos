#include "cli/lpm/LgsInstallCmd.h"
#include "errors/LgsCliErrors.h"
#include "files/LgsAppFile.h"

void LgsInstallCmd::run() {
    const fs::path path = argv[3];
    if (!fs::exists(path)) {
        return errHandler.addError(E40004, {path});
    }
    const auto appConfigPath = path / LGS_APP_FILE_NAME;
    if (!fs::exists(appConfigPath)) {
        return errHandler.addError(E40004, {appConfigPath});
    }
    pkgManager.paths.appConfigFile = appConfigPath;
    pkgManager.install();
}

LgsCliCmdHelp& LgsInstallCmd::getHelp() {
    return pkgInstallCmdHelp;
}
