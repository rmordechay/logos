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
    virtual bool run() = 0;
    virtual LgsCliCmdHelp& getHelp() = 0;
    virtual void printHelp();
    int32_t parseIntArg(int i, const std::string& cmd) const;
    std::string parseString(int& i, const std::string& cmd) const;
    void printArg(std::ostringstream& txt, LgsCliCmdArgHelp& arg) const;
    int parseArgs(int indexStart, const std::function<void(int, const std::string&)>& f) const;
    void getLongestArg(const LgsCliCmdHelp& help);
    std::string mergeArgs() const;
    virtual ~LgsCliCmd() = default;
};

std::string padString(size_t maxLen, const std::string& str = "");
void printParentCmdHelp(const std::vector<LgsCliCmdHelp*>& commands, const std::string& subCmd = "");
