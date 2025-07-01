#include "cli/LgsFormatCmd.h"

#include "files/LgsFile.h"
#include "logos/Logos.h"

void LgsFormatCmd::runCmd() {
    filePath = argv[2];
    Logos logos;
}

void LgsFormatCmd::validate() {
    if (argc < 3) printInfoAndExit("Too few arguments.\n");
}

void LgsFormatCmd::printHelp() {
    lgsLog("Usage: lgs format <path>\n\n");
}
