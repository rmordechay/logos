#include "cli/LgsRunCmd.h"
#include "logos/Logos.h"
#include <iostream>

void LgsRunCmd::runCmd() {
    validate();
    Logos logos(rootPath);
    setArgs(&logos);
    logos.run();
}

void LgsRunCmd::validate() {
    if (argc < 3) printInfoAndExit("Too few arguments.\n");
    const auto firstArg = argv[2];
    const bool isArgDotOrEmpty = std::strcmp(firstArg, ".") == 0 || argc < 3;
    if (isArgDotOrEmpty) {
        rootPath = current_path().string();
    } else {
        rootPath = firstArg;
    }
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
