#pragma once
#include "pch.h"

struct LgsCliCmdArgHelp {
    const char* name = "";
    const char* type = "";
    const char* defaultVal = "";
    const char* possibleValues = "";
    const char* desc = "";
    bool required = false;
};

struct LgsCliCmdHelp {
    std::string name = "";
    std::string usage = "";
    std::string error = "";
    std::vector<LgsCliCmdArgHelp> args;
    std::vector<LgsCliCmdArgHelp> opts;
};

class LgsCliCmd {
public:
    int argc;
    char** argv;
    std::string errMsg;

    LgsCliCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    virtual void run() = 0;
    virtual bool setup() = 0;
    virtual LgsCliCmdHelp& help() = 0;
    virtual ~LgsCliCmd() = default;
};
