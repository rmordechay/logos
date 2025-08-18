#pragma once
#include "utils/LgsUtils.h"

class LgsCmd {
public:
    int argc;
    char** argv;

    LgsCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    void printInfoAndExit();
    void printInfoAndExit(const std::string& msg);
    virtual void runCmd() = 0;
    virtual void validate() = 0;
    virtual void printHelp() = 0;
    virtual ~LgsCmd() = default;
};

inline void LgsCmd::printInfoAndExit() {
    printHelp();
    exit(1);
}

inline void LgsCmd::printInfoAndExit(const std::string& msg) {
    logInfo(msg);
    printInfoAndExit();
}


