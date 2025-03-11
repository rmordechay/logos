#include "cli/LogosRunCmd.h"
#include "Logos.h"
#include <iostream>

void LogosRunCmd::init(const int argc, char** argv) {
    if (argc < 3 || std::strcmp(argv[2], ".") == 0) {
        rootPath = current_path().string();
    } else {
        rootPath = argv[2];
    }
}

void LogosRunCmd::runCmd() {
    Logos project(rootPath);
    project.run();
}

void LogosRunCmd::printHelp() {
    std::cout << "Usage: lgs run [path] [options]" << "\n\n";
}

void LogosRunCmd::exitWithHelp(const string& errMsg) {
    cout << errMsg << "\n\n";
    printHelp();
    exit(0);
}
