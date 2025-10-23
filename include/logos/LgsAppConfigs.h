#pragma once
#include <cstdint>
#include <string>
#include <iostream>
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
    void printConfigs() const;
};

inline void LgsAppConfigs::printConfigs() const {
    std::cout << "name       = " << name << std::endl;
    std::cout << "activeEnv  = " << activeEnv << std::endl;
    std::cout << "logLevel   = " << logLevel << std::endl;
    std::cout << "version    = " << std::to_string(version.major) << '.' << std::to_string(version.minor) << '.'<< std::to_string(version.micro) << std::endl;
    std::cout << "debugMode  = " << debugMode << std::endl;
    std::cout << "isTestRun  = " << isTestRun << std::endl;
    std::cout << "isFileMode = " << isFileMode << std::endl;
    std::cout << "optLevel   = " << std::to_string(optLevel) << std::endl;
}
