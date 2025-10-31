#include "cli/commands/LgsGenerateCmd.h"
#include "data/LgsCliErrors.h"
#include "data/LgsFileTemplates.h"

void createProjectStructure(const std::string& name);

void LgsGenerateCmd::run() {
    if (argc != 3) exitWithError(E40001);
    const auto name = std::string(argv[2]);
    if (std::isdigit(name[0])) exitWithError(E40005, {name});
    for (const char c : name) {
        if (std::isupper(c)) exitWithError(E40005, {name});
        if (!std::isalpha(c) && c != '-') exitWithError(E40005, {name});
    }
    createProjectStructure(name);
}

LgsCliCmdHelp& LgsGenerateCmd::getHelp() {
    return generateCmdHelp;
}

void createProjectStructure(const std::string& name) {
    const auto projectDir = fs::current_path() / name;
    if (fs::exists(projectDir)) exitWithError(E40006, {name});
    fs::create_directories(projectDir);
    const auto srcDir = projectDir / "src";
    fs::create_directories(srcDir);
    const auto envsDir = projectDir / "envs";
    fs::create_directories(envsDir);

    const auto mainFile = srcDir / "Main.lgs";
    std::ofstream mainStream(mainFile);
    if (!mainStream) assert(0);
    mainStream << MAIN_FILE_TEMPLATE;
    mainStream.close();

    const auto appFile = projectDir / "App.lgs";
    std::ofstream appStream(appFile);
    if (!appStream) assert(0);
    char buffer[1024];
    std::snprintf(buffer, sizeof(buffer), APP_CONFIG_FILE_TEMPLATE, name.c_str());
    appStream << buffer;
    appStream.close();
}
