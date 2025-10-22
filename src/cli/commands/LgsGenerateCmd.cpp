#include "cli/commands/LgsGenerateCmd.h"
#include "data/LgsCliErrors.h"

void createProjectStructure(const std::string& name);

void LgsGenerateCmd::run() {
    if (argc != 3) exitWithError(E40001);
    const auto name = std::string(argv[2]);
    if (std::isdigit(name[0])) exitWithError(E40006, {name});
    for (const char c : name) {
        if (std::isupper(c)) exitWithError(E40006, {name});
        if (!std::isalpha(c) && c != '-') exitWithError(E40006, {name});
    }
    createProjectStructure(name);
}

LgsCliCmdHelp& LgsGenerateCmd::getHelp() {
    return generateCmdHelp;
}

void createProjectStructure(const std::string& name) {
    const auto projectDir = fs::current_path() / name;
    if (fs::exists(projectDir)) exitWithError(E40007, {name});
    fs::create_directories(projectDir);
    const auto srcDir = projectDir / "src";
    fs::create_directories(srcDir);
    const auto mainFile = srcDir / "Main.lgs";
    std::ofstream mainStream(mainFile);
    if (!mainStream) assert(0);
    mainStream.close();
    const auto appFile = projectDir / "App.lgs";
    std::ofstream appStream(appFile);
    if (!appStream) assert(0);
    appStream.close();
}
