#include "cli/LogosRunCmd.h"
#include "Logos.h"
#include <iostream>

void LogosRunCmd::runCmd(const int argc, char** argv) {
    initRootPath(argc, argv);
    Logos project(rootPath);
    project.run();
}

void LogosRunCmd::initRootPath(const int argc, char** argv) {
    const auto firstArg = argv[2];
    const bool isArgDotOrEmpty = std::strcmp(firstArg, ".") == 0 || argc < 3;
    if (isArgDotOrEmpty) {
        rootPath = current_path().string();
    } else {
        rootPath = firstArg;
    }
}

void LogosRunCmd::printHelp() {
    std::cout << "Usage: lgs run [path] [options]" << "\n\n";
}
