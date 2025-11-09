#pragma once
#include "LgsCliCmd.h"

class LgsCli {
public:
    int argc;
    char** argv;

    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    bool execute() const;
    LgsCliCmd* getCmd() const;
};

inline LgsCliCmdHelp lgsVersionCmdHelp{
    .name = "version",
    .usage = "lgs version",
    .summary = "Prints Logos version.",
    .desc = "prints the version of the current lgs binary.",
    .examples = {
        "lgs version",
    }
};

inline LgsCliCmdHelp lgsHelpCmdHelp{
    .name = "help",
    .usage = "lgs help",
    .summary = "Prints Logos help.",
    .desc = "prints the main help of for lgs.",
    .examples = {
        "lgs help",
    }
};
