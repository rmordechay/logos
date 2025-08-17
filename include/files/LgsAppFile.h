#pragma once
#include "LgsFile.h"
#include "configs/LgsDefinitions.h"
#include "stmts/LgsVarDec.h"
#include <regex>

class LgsVarDec;

struct LgsAppVersion {
    int major;
    int minor;
    int micro;
};

class LgsAppFile final : public LgsFile {
public:
    std::string activeEnv = "Pro";
    LgsAppVersion version{1, 0, 0};
    std::vector<LgsVarDec*> requireEnvVars;
    std::vector<std::string> requirePackages;

    explicit LgsAppFile(const size_t fileID, const fs::path& path) : LgsFile(fileID, LGS_APP_FILE_NAME, path) {}
    bool parseVersion(const char* versionStr);
    ~LgsAppFile() override = default;
};

inline bool LgsAppFile::parseVersion(const char* versionStr) {
    int consumed = 0;
    if (std::sscanf(versionStr, "%d.%d.%d%n", &version.major, &version.minor, &version.micro, &consumed) == 3) {
        return versionStr[consumed] == '\0';
    }
    return false;
}
