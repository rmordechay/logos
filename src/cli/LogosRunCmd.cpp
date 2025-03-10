#include "cli/LogosRunCmd.h"
#include "Application.h"
#include <iostream>

void LogosRunCmd::init(const int argc, char** argv) {
    if (argc < 3 || std::strcmp(argv[2], ".") == 0) {
        rootPath = current_path().string();
    } else {
        rootPath = argv[2];
    }
    string srcDir;
    for (const auto& entry : directory_iterator(rootPath)) {
        auto fileName = entry.path().filename();
        if (entry.is_directory() && fileName == LOGOS_SRC_PATH) {
            srcDir = entry.path().string();
        }
    }
    if (srcDir.empty()) {
        exitWithMessage("Logos project must have 'src' directory");
    }
}

void LogosRunCmd::runCmd() {
    Application project(rootPath);
    project.runLogos();
}

void LogosRunCmd::printHelp() {
    std::cout << "Usage: lgs run [path] [options]" << "\n\n";
}

void LogosRunCmd::exitWithMessage(const string& errMsg) {
    cout << errMsg << '\n';
    exit(0);
}

void LogosRunCmd::exitWithHelp(const string& errMsg) {
    cout << errMsg << "\n\n";
    printHelp();
    exit(0);
}
