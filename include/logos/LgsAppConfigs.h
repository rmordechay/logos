#pragma once

#define INITIAL_ARRAY_CAPACITY 2
#define BIG_SIZE_THRESHOLD 4
#define STACK_CAPACITY 8
#define LOCALS_CAPACITY 8

enum LgsLogLevel {
    INFO,
    DEBUG,
    ERROR,
};

struct LgsAppConfigs {
    std::string name = "app";
    uint8_t optLevel = 2;
    bool debugMode = false;
    bool writeIRFile = true;
    LgsLogLevel logLevel = DEBUG;
    std::string activeEnv = "Pro";
    struct { int major; int minor; int micro; } version{1, 0, 0};
};
