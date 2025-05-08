#include "cli/LgsRunCmd.h"
#include "Logos.h"
#include <iostream>

void LgsRunCmd::runCmd() {
    validate();
    Logos project(rootPath);
    project.run(argc, argv);
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

void LgsRunCmd::printHelp() {
    std::cout << "Usage: lgs run <path> <options>" << "\n\n";
}
