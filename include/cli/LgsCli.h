#pragma once
#include "LgsCliCmd.h"

class LgsCli {
public:
    int argc;
    char** argv;

    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    void execute() const;
    void runCmd(LgsCliCmd& cmd) const;
};

inline LgsCliCmdHelp versionCmdHelp{
    .name = "version",
    .usage = "lgs version",
    .summary = "Prints Logos version.",
    .desc = "The version command prints the version of the current lgs binary.",
    .examples = {
        "lgs version",
    }
};

inline LgsCliCmdHelp helpCmdHelp{
    .name = "help",
    .usage = "lgs help",
    .summary = "Prints Logos help.",
    .desc = "The help command prints the main help of for lgs.",
    .examples = {
        "lgs help",
    }
};