#include "cli/LgsCliCmd.h"

#include <__ostream/basic_ostream.h>
#include <_ctype.h>
#include <_string.h>
#include <assert.h>
#include <sstream>
#include <algorithm>
#include <iomanip>

#include "cli/LgsCliHelp.h"
#include "LgsDefinitions.h"
#include "LgsUtils.h"

void LgsCliCmd::printHelp() {
    const auto h = getHelp();
    assert(h.name != "" && h.usage != "" && h.desc != "" && !h.examples.empty());
    getLongestArg(h);
    std::ostringstream txt;
    txt << LGS_COLORIZE("Help\n", LGS_MSG_COLOR_WHITE);
    txt << LGS_USAGE_STR << h.usage << "\n";

    // Required
    if (!h.requiredArgs.empty()) {
        txt << '\n' << LGS_COLORIZE("Required:", LGS_MSG_COLOR_WHITE) << '\n';
        for (auto arg : h.requiredArgs) {
            printArg(txt, arg);
        }
        txt << "\n";
    }

    // Options
    if (!h.optionalArgs.empty()) {
        txt << LGS_COLORIZE("Options:", LGS_MSG_COLOR_WHITE) << '\n';
        for (auto arg : h.optionalArgs) {
            printArg(txt, arg);
            txt << "\n";
        }
    }

    // Description
    txt << LGS_COLORIZE("\nDescription", LGS_MSG_COLOR_WHITE) << '\n';
    txt << h.desc << "\n";

    // Examples
    txt << LGS_COLORIZE("\nExamples:", LGS_MSG_COLOR_WHITE) << '\n';
    for (const auto& example : h.examples) {
        txt << example << '\n';
    }

    logInfo(txt.str());
}

int LgsCliCmd::parseArgs(const int indexStart, const std::function<void(const std::string&, int&)>& f) const {
    auto argStart = -1;
    for (int i = indexStart; i < argc; ++i) {
        const auto arg = argv[i];
        if (arg[0] != '-') {
            argStart = i;
            break;
        }
        const auto name = std::string(arg).substr(arg[1] == '-' ? 2 : 1);
        f(name, i);
    }
    return argStart;
}

bool LgsCliCmd::isArgEqual(const std::string& arg1, const std::vector<std::string>& args) {
    for (auto arg2 : args) {
        // e.g. -o 3 or -o3
        const auto isSingleLetter = arg2.length() == 1 || (arg2.length() == 2 && isdigit(arg2[1]));
        if (isSingleLetter && arg2 == arg1.substr(0, arg1.length() - 1)) return true;
        if (arg1 == arg2) return true;
    }
    return false;
}

void LgsCliCmd::getLongestArg(const LgsCliCmdHelp& help) {
    size_t longestStr = 0;
    for (const auto& arg : help.requiredArgs) {
        longestStr = std::max(longestStr, arg.name.length());
    }
    for (const auto& arg : help.optionalArgs) {
        longestStr = std::max(longestStr, arg.name.length());
        longestStr = std::max(longestStr, arg.name2.length());
    }
    const auto minSize = std::strlen(LGS_USAGE_STR);
    if (longestStr < minSize) longestStr = minSize;
    maxStr = longestStr;
}

void LgsCliCmd::printArg(std::ostringstream& txt, LgsCliCmdArgHelp& arg) const {
    txt << padString(maxStr, arg.name);
    txt << padString(maxStr, arg.desc) << '\n';
    txt << padString(maxStr, arg.name2);
    if (!arg.type.empty()) {
        txt << "Type: " << arg.type << ".\n";
    }
    if (!arg.defaultVal.empty()) {
        txt << padString(maxStr) + "Default: " << arg.defaultVal << ".\n";
    }
    if (!arg.possibleValues.empty()) {
        txt << padString(maxStr) + "Possible value: " << arg.possibleValues << ".\n";
    }
}

std::string LgsCliCmd::parseString(int& i, const std::string& cmd) const {
    const auto code = argv[++i];
    const auto firstChar = code[0];
    if (firstChar == '"' || firstChar == '\'') {
        return cmd.substr(1, cmd.size() - 2);
    }
    return "";
}

std::string LgsCliCmd::mergeArgs() const {
    std::stringstream str;
    str << "lgs ";
    for (int i = 1; i < argc; ++i) {
        str << argv[i] << ' ';
    }
    return str.str();
}

std::string padString(const size_t maxLen, const std::string& str) {
    int diff = maxLen - str.length();
    if (diff < 0) diff = -diff;
    return str + std::string(diff + PADDING, ' ');
}

void printParentCmdHelp(const std::vector<LgsCliCmdHelp*>& commands, const std::string& subCmd) {
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
