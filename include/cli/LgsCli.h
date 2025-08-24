#pragma once
#include "LgsCliCmd.h"

class LgsCli {
public:
    int argc;
    char** argv;
    std::string cmdStr;

    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {
        joinCmdStr();
    }
    void joinCmdStr();
    void execute() const;
    void runCmd(LgsCliCmd& cmd) const;
    bool isHelpCmd() const;
};
