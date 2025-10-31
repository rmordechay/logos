#pragma once
#include "LgsCliHelp.h"
#include "logos/LgsApp.h"

struct LgsCliCmdHelp;

class LgsCliCmd {
public:
    int argc;
    char** argv;
    size_t maxStr = 0;

    LgsCliCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    virtual void run() = 0;
    virtual LgsCliCmdHelp& getHelp() = 0;
    void printHelp();
    void getLongestArg(const LgsCliCmdHelp& help);
    std::string padString(const std::string& str = "") const;
    void printArg(std::ostringstream& txt, LgsCliCmdArgHelp& arg) const;
    int32_t parseInt(int& i, const std::string& cmd) const;
    std::string parseString(int& i, const std::string& cmd) const;
    virtual ~LgsCliCmd() = default;
};
