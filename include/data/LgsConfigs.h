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

enum LgsArch {
    UNKNOWN_ARCH,
    X86_64,
    AARCH64,
};

struct LgsConfigs {
    LgsOS os;
    LgsArch arch;
    bool devMode = true;
    bool printIR = true;
    bool writeIRFiles = false;

    LgsConfigs() {
        setOS();
        setArch();
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
        assert(0);
#endif
    }

    void setArch() {
#if defined(__x86_64__) || defined(_M_X64)
        arch = X86_64;
#elif defined(__aarch64__)
        arch = AARCH64;
#endif
    }
};

inline LgsConfigs lgsConfigs;
