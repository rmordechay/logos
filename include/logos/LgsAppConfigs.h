#pragma once
#include "utils/LgsUtils.h"
#include <cstdint>
#include <string>

enum LgsAppLogLevel {
    APP_INFO,
    APP_DEBUG,
    APP_ERROR,
};

struct LgsAppVersion {
    size_t major;
    size_t minor;
    size_t micro;
};

struct LgsAppConfigs {
    std::string name = "";
    std::string activeEnv = "";
    LgsAppVersion version{1, 0, 0};
    LgsAppLogLevel logLevel = APP_INFO;
    bool debugMode = false;
    bool isTestRun = false;
    bool isFileMode = false;
    uint8_t optLevel = 2;

    void print() const;
};

inline void LgsAppConfigs::print() const {
    logInfo("name       = " + name + '\n');
    logInfo("activeEnv  = " + activeEnv + '\n');
    logInfo("logLevel   = " + std::to_string(logLevel) + '\n');
    logInfo("version    = " + std::to_string(version.major) + '.' + std::to_string(version.minor) + '.'+ std::to_string(version.micro) + '\n');
    logInfo("debugMode  = " + std::to_string(debugMode) + '\n');
    logInfo("isTestRun  = " + std::to_string(isTestRun) + '\n');
    logInfo("isFileMode = " + std::to_string(isFileMode) + '\n');
    logInfo("optLevel   = " + std::to_string(optLevel) + '\n');
}
