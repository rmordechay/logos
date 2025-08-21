#pragma once
#include "LgsCliHelp.h"
#include "pch.h"

struct LgsCliCmdHelp;

class LgsCliCmd {
public:
    int argc;
    char** argv;
    size_t maxStr = 0;
    const std::string unknownCmd = "Unknown command";

    LgsCliCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    virtual void run() = 0;
    virtual LgsCliCmdHelp& getHelp() = 0;
    void printHelp();
    void getLongestArg(const LgsCliCmdHelp& help);
    void printArg(std::ostringstream& txt, LgsCliCmdArgHelp& arg) const;
    void exitWithError(const std::string& msg);
    std::string padString(const std::string& str = "") const;
    virtual ~LgsCliCmd() = default;
};
