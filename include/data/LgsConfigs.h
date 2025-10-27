#pragma once

#define STACK_CAPACITY 1024
#define LOCALS_CAPACITY 8
#define BIG_SIZE_THRESHOLD 4

enum LgsOS {
    UnknownOS,
    MacOS,
    Linux,
    Windows,
};

struct LgsConfigs {
    LgsOS os = UnknownOS;
    bool debug = true;
    bool writeIRFiles = false;

    LgsConfigs() {
#ifdef __APPLE__
        os = MacOS;
#elif defined(_WIN32)
        os = Windows;
#elif defined(__linux__)
        os = Linux;
#endif
    }
};

inline LgsConfigs lgsConfigs;
