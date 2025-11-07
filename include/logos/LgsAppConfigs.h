#pragma once
#include "LgsConfigs.h"
#include "data/LgsVersion.h"
#include "utils/LgsUtils.h"
#include <cstdint>
#include <string>

enum LgsAppMode {
    CODE_MODE,
    FILE_MODE,
    PROJECT_MODE,
    PKG_MANAGER_MODE,
    UNKNOWN_MODE,
};

struct LgsAppConfigs {
    std::string name = "";
    std::string activeEnv = "";
    LgsVersion version{0, 0, 0};
    LgsLogLevel logLevel = LGS_INFO;
    LgsAppMode appMode = UNKNOWN_MODE;
    uint8_t optLevel = 0;
    bool debugMode = false;
    bool isTestRun = false;
    bool isLibrary = false;
};

inline void print(const LgsAppConfigs& configs) {
    logInfo("name       = " + configs.name + '\n');
    logInfo("activeEnv  = " + configs.activeEnv + '\n');
    logInfo("logLevel   = " + std::to_string(configs.logLevel) + '\n');
    logInfo("version    = " + configs.version.asStr() + '\n');
    logInfo("debugMode  = " + std::to_string(configs.debugMode) + '\n');
    logInfo("isTestRun  = " + std::to_string(configs.isTestRun) + '\n');
    logInfo("isLibrary  = " + std::to_string(configs.isLibrary) + '\n');
    logInfo("fileMode   = " + std::to_string(configs.appMode) + '\n');
    logInfo("optLevel   = " + std::to_string(configs.optLevel) + '\n');
}

