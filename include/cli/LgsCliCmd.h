#pragma once
#include "LgsCliHelp.h"
#include "logos/LgsApp.h"
#include "utils/LgsErrHandler.h"

#include <iostream>
struct LgsCliCmdHelp;

#define PADDING 4
#define LGS_USAGE_STR "Usage: "

class LgsCliCmd {
public:
    int argc;
    char** argv;
    size_t maxStr = 0;

    LgsCliCmd(const int argc, char** argv) : argc(argc), argv(argv) {}
    virtual void run() = 0;
    virtual LgsCliCmdHelp& getHelp() = 0;
    virtual void printHelp();
    void getLongestArg(const LgsCliCmdHelp& help);
    void printArg(std::ostringstream& txt, LgsCliCmdArgHelp& arg) const;
    int32_t parseInt(int& i, const std::string& cmd) const;
    std::string parseString(int& i, const std::string& cmd) const;
    std::string mergeArgs() const;
    virtual ~LgsCliCmd() = default;
};

inline std::string padString(const size_t maxLen, const std::string& str = "") {
    int diff = maxLen - str.length();
    if (diff < 0) diff = -diff;
    return str + std::string(diff + PADDING, ' ');
}

inline void printParentCmdHelp(const std::vector<LgsCliCmdHelp*>& commands, const std::string& subCmd = "") {
    size_t longestStr = 0;
    std::ostringstream txt;
    txt << LGS_COLORIZE("Help\n", LGS_MSG_COLOR_WHITE);
    for (auto& help : commands) {
        longestStr = std::max(longestStr, help->name.size());
    }
    txt << padString(longestStr, LGS_USAGE_STR);
    if (subCmd == "") {
        txt << "lgs <command> <options> <arguments>\n\n";
    } else {
        txt << "lgs " << subCmd << " <options> <arguments>\n\n";
    }
    txt << LGS_COLORIZE("Commands\n", LGS_MSG_COLOR_WHITE);
    for (auto& help : commands) {
        txt << std::left << std::setw(longestStr + 4) << help->name << help->summary << '\n';
    }
    txt << "\nFor more information run 'lgs <command> help'.\n";
    logInfo(txt.str());
}
