#pragma once
#include "LgsCliCmd.h"

void printLgsHelp();
void printHelp(LgsCliCmd& cmd);

class LgsCli {
public:
    int argc;
    char** argv;
    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    void runCmd(LgsCliCmd& cmd) const;
    static void printHelp(LgsCliCmd& cmd);
    void execute() const;
};
