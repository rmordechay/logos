#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include <pch.h>

class LgsCli {
public:
    int argc;
    char** argv;

    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    static void printVersion();
    void execute() const;
    static void printHelp();
    static void exitWithMsg(const std::string& errorMsg);
    ~LgsCli() = default;
};

#endif //COMMANDLINE_H
