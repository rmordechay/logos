#include "cli/LgsCliCmd.h"
#include "cli/LgsCliHelp.h"
#include "configs/LgsDefinitions.h"
#include "utils/LgsUtils.h"

#define PADDING 6
#define USAGE_STR "Usage:"

void LgsCliCmd::printHelp() {
    const auto h = getHelp();
    assert(h.name != "" && h.usage != "" && h.desc != "" && !h.examples.empty());
    std::ostringstream txt;

    txt << LGS_COLORIZE("Help", LGS_MSG_COLOR_WHITE) << '\n';
    getLongestArg(h);
    txt << padString(USAGE_STR) << h.usage << "\n";

    // Required
    if (!h.requiredArgs.empty()) {
        txt << '\n' << LGS_COLORIZE("Required:", LGS_MSG_COLOR_WHITE) << '\n';
    }
    for (auto arg : h.requiredArgs) {
        printArg(txt, arg);
        txt << '\n';
    }

    // Optionals
    if (!h.optionalArgs.empty()) {
        txt << LGS_COLORIZE("Options:", LGS_MSG_COLOR_WHITE) << '\n';
    }
    for (auto arg : h.optionalArgs) {
        printArg(txt, arg);
        txt << '\n';
    }

    // Examples
    txt << LGS_COLORIZE("Examples:", LGS_MSG_COLOR_WHITE) << '\n';
    for (const auto& example : h.examples) {
        txt << example << '\n';
    }

    // Description
    txt << LGS_COLORIZE("\nDescription", LGS_MSG_COLOR_WHITE) << '\n';
    txt << h.desc << "\n";

    logInfo(txt.str());
}

void LgsCliCmd::printArg(std::ostringstream& txt, LgsCliCmdArgHelp& arg) const {
    auto [name, type, defaultVal, possibleValues, desc] = arg;
    txt << padString(name);
    txt << padString(desc) << '\n';
    if (!type.empty()) {
        txt << padString() + "Type: " << type << ".\n";
    }
    if (!defaultVal.empty()) {
        txt << padString() + "Default: " << defaultVal << ".\n";
    }
    if (!possibleValues.empty()) {
        txt << padString() + "Possible value: " << possibleValues << ".\n";
    }
}

void LgsCliCmd::exitWithError(const std::string& msg) {
    logError(msg);
    printHelp();
    exit(1);
}

std::string LgsCliCmd::padString(const std::string& str) const {
    int diff = maxStr - str.length();
    if (diff < 0) diff = -diff;
    return str + std::string(diff + PADDING, ' ');
}

;

void LgsCliCmd::getLongestArg(const LgsCliCmdHelp& help) {
    size_t longestStr = 0;
    for (const auto& arg : help.requiredArgs) {
        longestStr = std::max(longestStr, arg.name.length());
    }
    const auto minSize = std::strlen(USAGE_STR);
    if (longestStr < minSize) longestStr = minSize;
    maxStr = longestStr;
}
