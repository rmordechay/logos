#include "cli/LgsRunCmd.h"
#include "logos/Logos.h"


void LgsRunCmd::runCmd() {
    const auto firstArg = argv[2];
    const auto isCurrentDirOrEmpty = strcmp(firstArg, ".") == 0 || argc == 2;
    const auto rootPath = isCurrentDirOrEmpty ? current_path().string() : firstArg;
    Logos logos(rootPath);
    setArgs(&logos);
    logos.run();
}

void LgsRunCmd::validate() {
    if (argc < 3) printInfoAndExit("Too few arguments.\n");
}

void LgsRunCmd::setArgs(Logos* logos) const {
    vector<char*> args;
    for (int i = 0; i < argc; ++i) {
        logos->args.emplace_back(argv[i]);
    }
}

void LgsRunCmd::printHelp() {
    std::cout << "Usage: lgs run <path> <options>" << "\n\n";
}
