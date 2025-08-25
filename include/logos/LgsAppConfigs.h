#pragma once

enum LgsLogLevel {
    INFO,
    DEBUG,
    ERROR,
};

struct LgsAppConfigs {
    std::string name = "app";
    uint8_t optLevel = 2;
    bool debugMode = false;
    LgsLogLevel logLevel = INFO;
    std::string activeEnv = "Pro";
    struct { int major; int minor; int micro; } version{1, 0, 0};
};
