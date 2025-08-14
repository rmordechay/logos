#include "cli/LgsRunCmd.h"

void LgsRunCmd::runCmd() {
    const auto firstArg = argv[2];
    const auto isCurrentDirOrEmpty = strcmp(firstArg, ".") == 0 || argc == 2;
    const auto rootPath = isCurrentDirOrEmpty ? fs::current_path().string() : firstArg;
    LgsApp logos(rootPath);
    setArgs(&logos);
    logos.run();
}

void LgsRunCmd::validate() {
    if (argc < 3) printInfoAndExit("Too few arguments.\n");
}

void LgsRunCmd::setArgs(LgsApp* app) const {
    std::vector<char*> args;
    for (int i = 0; i < argc; ++i) {
        app->args.emplace_back(argv[i]);
    }
}

void LgsRunCmd::printHelp() {
    logInfo("Usage: lgs run <path> <options>\n");
}
