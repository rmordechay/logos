#pragma once
#include "stmts/LgsVarDec.h"
#include <regex>

class LgsVarDec;

struct LgsAppVersion {
    int major;
    int minor;
    int micro;
};

class LgsAppInfo final {
public:
    std::string name = "main";
    std::string activeEnv = "Pro";
    LgsAppVersion version{1, 0, 0};
    LgsLocation location{0, 0, nullptr};
    std::vector<LgsVarDec*> requireEnvVars;
    std::vector<std::string> requirePackages;
    fs::path appFilePath;

    ~LgsAppInfo() = default;
    bool parseVersion(const char* versionStr);
};

inline bool LgsAppInfo::parseVersion(const char* versionStr) {
    int consumed = 0;
    if (std::sscanf(versionStr, "%d.%d.%d%n", &version.major, &version.minor, &version.micro, &consumed) == 3) {
        return versionStr[consumed] == '\0';
    }
    return false;
}
