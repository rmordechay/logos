#include "cli/commands/LgsGenerateCmd.h"
#include "data/LgsCliErrors.h"
#include "data/LgsFileTemplates.h"

void LgsGenerateCmd::run() {
    if (argc != 3) {
        return errHandler.addError(E40001);
    }
    const auto name = std::string(argv[2]);
    if (std::isdigit(name[0])) {
        return errHandler.addError(E40005, {name});
    }
    for (const char c : name) {
        if (std::isupper(c)) {
            return errHandler.addError(E40005, {name});
        }
        if (!std::isalpha(c) && c != '-') {
            return errHandler.addError(E40005, {name});
        }
    }
    createProjectStructure(name);
}

LgsCliCmdHelp& LgsGenerateCmd::getHelp() {
    return generateCmdHelp;
}

void LgsGenerateCmd::createProjectStructure(const std::string& name) const {
    auto projectDir = fs::current_path() / name;
    if (fs::exists(projectDir)) return printCliError(E40006, {name});
    createDir(projectDir);
    auto srcDir = projectDir / LGS_SRC_DIR;
    createDir(srcDir);
    auto envsDir = projectDir / LGS_ENVS_DIR;
    createDir(envsDir);

    const auto mainFile = srcDir / LGS_MAIN_FILE;
    std::ofstream mainStream(mainFile);
    if (!mainStream) assert(0);
    mainStream << MAIN_FILE_TEMPLATE;
    mainStream.close();

    const auto appFile = projectDir / LGS_APP_FILE_NAME;
    std::ofstream appStream(appFile);
    if (!appStream) assert(0);
    char buffer[1024];
    std::snprintf(buffer, sizeof(buffer), APP_CONFIG_FILE_TEMPLATE, name.c_str());
    appStream << buffer;
    appStream.close();
}
