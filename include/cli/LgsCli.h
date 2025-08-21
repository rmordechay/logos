#pragma once
#include "LgsCliCmd.h"

class LgsCli {
public:
    int argc;
    char** argv;

    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    void execute() const;
    void runCmd(LgsCliCmd& cmd) const;
    bool isHelpCmd() const;
};
