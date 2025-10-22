#pragma once
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
    std::string name = "App";
    std::string activeEnv = "";
    LgsAppVersion version{1, 0, 0};
    LgsAppLogLevel logLevel = APP_INFO;
    bool debugMode = false;
    bool isTestRun = false;
    bool isFileMode = false;
    uint8_t optLevel = 2;
};
