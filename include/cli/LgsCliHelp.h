#pragma once
#include <string>
#include <vector>

struct LgsCliCmdArgHelp {
    std::string name = "";
    std::string type = "";
    std::string defaultVal = "";
    std::string possibleValues = "";
    std::string desc = "";
};

struct LgsCliCmdHelp {
    std::string name = "";
    std::string usage = "";
    std::string summary = "";
    std::string desc = "";
    std::string error = "";
    std::vector<LgsCliCmdArgHelp> requiredArgs = {};
    std::vector<LgsCliCmdArgHelp> optionalArgs = {};
    std::vector<std::string> examples = {};
};
