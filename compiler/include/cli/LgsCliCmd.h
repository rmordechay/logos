#pragma once
#include "LgsCliHelp.h"
#include "logos/LgsApp.h"
#include <iostream>
struct LgsCliCmdHelp;

#define PADDING 4
#define LGS_USAGE_STR "Usage: "

class LgsCliCmd {
public:
    int argc;
    char** argv;
    size_t maxStr = 0;
    LgsErrHandler errHandler;

    LgsCliCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    virtual void run() = 0;
    virtual LgsCliCmdHelp& getHelp() = 0;
    virtual void printHelp();
    std::string parseString(int& i, const std::string& cmd) const;
    static bool isArgEqual(const std::string& arg1, const std::vector<std::string>& args);
    void printArg(std::ostringstream& txt, LgsCliCmdArgHelp& arg) const;
    int parseArgs(int indexStart, const std::function<void(const std::string&, int&)>& f) const;
    void getLongestArg(const LgsCliCmdHelp& help);
    std::string mergeArgs() const;
    virtual ~LgsCliCmd() = default;
};

std::string padString(size_t maxLen, const std::string& str = "");
void printParentCmdHelp(const std::vector<LgsCliCmdHelp*>& commands, const std::string& subCmd = "");
