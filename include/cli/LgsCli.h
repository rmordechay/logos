#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include "logos/Logos.h"

using namespace std;

class LgsCli {
public:
    int argc;
    char** argv;

    LgsCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    static void printVersion();
    void execute() const;
    static void printHelp();
    static void exitWithMsg(const string& errorMsg);
    ~LgsCli() = default;
};

#endif //COMMANDLINE_H
