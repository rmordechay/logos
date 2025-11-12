#pragma once
#include "LgsCliCmd.h"

class LgsCliHandler {
public:
    int argc;
    char** argv;

    LgsCliHandler(const int argc, char** argv) : argc(argc), argv(argv) {}
    bool execute() const;
    LgsCliCmd* getCmd() const;
};

inline LgsCliCmdHelp lgsVersionCmdHelp{
    .name = "version",
    .name2 = "--version",
    .usage = "lgs version",
    .summary = "Prints Logos version.",
    .desc = "prints the version of the current lgs binary.",
    .examples = {
        "lgs version",
    }
};

inline LgsCliCmdHelp lgsHelpCmdHelp{
    .name = "help",
    .name2 = "--help",
    .usage = "lgs help",
    .summary = "Prints Logos help.",
    .desc = "prints the main help For Logos.",
    .examples = {
        "lgs help",
    }
};

inline bool isHelpCommand(const std::string& cmdStr) {
    return cmdStr == lgsHelpCmdHelp.name || cmdStr == lgsHelpCmdHelp.name2;
}

inline bool isVersionCommand(const std::string& cmdStr) {
    return cmdStr == lgsVersionCmdHelp.name || cmdStr == lgsVersionCmdHelp.name2;
}
