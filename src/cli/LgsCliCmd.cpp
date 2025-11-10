#include "cli/LgsCliCmd.h"
#include "cli/LgsCliHelp.h"
#include "data/LgsDefinitions.h"
#include "utils/LgsUtils.h"

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
    auto [name, name2, type, defaultVal, possibleValues, desc] = arg;
    txt << padString(maxStr, name);
    txt << padString(maxStr, desc) << '\n';
    txt << padString(maxStr, name2);
    if (!type.empty()) {
        txt << "Type: " << type << ".\n";
    }
    if (!defaultVal.empty()) {
        txt << padString(maxStr) + "Default: " << defaultVal << ".\n";
    }
    if (!possibleValues.empty()) {
        txt << padString(maxStr) + "Possible value: " << possibleValues << ".\n";
    }
}

int32_t LgsCliCmd::parseInt(int& i, const std::string& cmd) const {
    if (cmd.size() == 1) {
        return argv[++i][0] - '0';
    }
    if (cmd.size() == 2) {
        return cmd[1] - '0';
    }
    return -1;
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
