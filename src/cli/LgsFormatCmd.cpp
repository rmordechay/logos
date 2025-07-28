#include "cli/LgsFormatCmd.h"

void LgsFormatCmd::runCmd() {
    filePath = argv[2];
}

void LgsFormatCmd::validate() {
    if (argc < 3) printInfoAndExit("Too few arguments.\n");
}

void LgsFormatCmd::printHelp() {
    logInfo("Usage: lgs format <path>\n\n");
}
