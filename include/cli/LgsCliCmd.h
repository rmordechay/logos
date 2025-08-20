#pragma once
#include "pch.h"
#include "configs/LgsDefinitions.h"
#include "utils/LgsUtils.h"

#define PADDING 6
#define USAGE_STR "Usage:"

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
    const std::string unknownCmd = "Unknown command";

    LgsCliCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    void printHelp();

    virtual void run() = 0;
    virtual bool setup() = 0;
    virtual LgsCliCmdHelp& getHelp() = 0;
    virtual ~LgsCliCmd() = default;
};

inline size_t getLongestStrSize(const LgsCliCmdHelp& help) {
    size_t longestStr = 0;
    for (const auto& arg : help.args) {
        longestStr = std::max(longestStr, std::strlen(arg.name));
    }
    for (const auto& opt : help.opts) {
        longestStr = std::max(longestStr, std::strlen(opt.name));
    }
    const auto minSize = std::strlen(USAGE_STR);
    if (longestStr < minSize) longestStr = minSize;
    return longestStr;
}

inline void LgsCliCmd::printHelp() {
    const auto h = getHelp();
    std::ostringstream txt;
    txt << LGS_COLORIZE("Help", LGS_MSG_COLOR_WHITE) << '\n';

    const auto maxStr = getLongestStrSize(h);
    auto padString = [maxStr](const std::string& str) {
        int diff = maxStr - str.length();
        if (diff < 0) diff = -diff;
        return str + std::string(diff + PADDING, ' ');
    };

    txt << padString(USAGE_STR) << h.usage << "\n";

    // Required args
    if (!h.args.empty()) {
        txt << '\n' << LGS_COLORIZE("Required Arguments:", LGS_MSG_COLOR_WHITE) << '\n';
        for (const auto arg : h.args) {
            txt << padString(arg.name)
                << padString(arg.desc)
                << '\n';
        }
    }


    if (!h.opts.empty()) {
        txt << '\n' << LGS_COLORIZE("Options:", LGS_MSG_COLOR_WHITE) << '\n';
        for (auto arg : h.opts) {
            txt << padString(arg.name)
                << std::string(arg.desc)
                << std::string(arg.type)
                << arg.defaultVal << '\n';
        }
    }
    logInfo(txt.str());
}
