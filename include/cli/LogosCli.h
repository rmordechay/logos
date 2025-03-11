#ifndef COMMANDLINE_H
#define COMMANDLINE_H
#include "LogosCliCmd.h"
#include "application/Logos.h"

using namespace std;

class LogosCli {
public:
    int argc;
    char** argv;

    LogosCli(const int argc, char** argv) : argc(argc), argv(argv) {}
    static void printVersion();
    void execute() const;
    static void printHelp();
    static void exitWithMsg(const string& errorMsg);
    ~LogosCli() = default;
};

#endif //COMMANDLINE_H
