#include "cli/LgsFormatCmd.h"
#include "logos/Logos.h"

void LgsFormatCmd::runCmd() {
    filePath = argv[2];
    Logos logos;
    logos.project.parseSrcFile(filePath);
    logos.project.files.front()->format();
}

void LgsFormatCmd::validate() {
    if (argc < 3) printInfoAndExit("Too few arguments.\n");
}

void LgsFormatCmd::printHelp() {
    std::cout << "Usage: lgs format <path>" << "\n\n";
}
