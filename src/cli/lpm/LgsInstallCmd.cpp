#include "cli/lpm/LgsInstallCmd.h"
#include "data/LgsCliErrors.h"
#include "files/LgsAppConfigFile.h"

bool LgsInstallCmd::run() {
    const fs::path path = argv[3];
    if (!fs::exists(path)) {
        printCliError(E40004, {path});
        return false;
    }
    const auto appConfigPath = path / LGS_APP_FILE_NAME;
    if (!fs::exists(appConfigPath)) {
        printCliError(E40004, {appConfigPath});
        return false;
    }
    pkgManager.paths.appConfigFile = appConfigPath;
    pkgManager.install();
    return true;
}

LgsCliCmdHelp& LgsInstallCmd::getHelp() {
    return pkgInstallCmdHelp;
}
