#pragma once
#include <string>

#define STACK_CAPACITY 1024
#define LOCALS_CAPACITY 8
#define BIG_SIZE_THRESHOLD 4

enum LgsOS {
    UNKNOWN_OS,
    MAC_OS,
    LINUX,
    WINDOWS,
};

struct LgsConfigs {
    LgsOS os;
    bool devMode = false;
    bool printIR = true;
    bool writeIRFiles = false;

    LgsConfigs() {
        setOS();
        if (const char* env = std::getenv("LGS_DEV_MODE")) {
            devMode = std::string(env) == "1" || std::string(env) == "true";
        }
    }

    void setOS() {
#ifdef __APPLE__
        os = MAC_OS;
#elif defined(_WIN32)
        os = WINDOWS;
#elif defined(__linux__)
        os = LINUX;
#else
        assert(0)
#endif
    }
};

inline LgsConfigs lgsConfigs;
