#pragma once
#include <string>
#include <cstdlib>

#define BIG_SIZE_THRESHOLD 4
#define STRING_BUFFER_SIZE 1024
#define MAX_ELEMENT_SIZE 1024*100

enum LgsLogLevel {
    LGS_INFO,
    LGS_DEBUG,
};

enum LgsOS {
    MAC_OS,
    LINUX,
    WINDOWS,
    UNKNOWN_OS,
};

enum LgsArch {
    X86_64,
    AARCH64,
    UNKNOWN_ARCH,
};

struct LgsConfigs {
    LgsOS os;
    LgsArch arch;
    bool isDevMode = true;
    bool printIR = true;
    bool writeIRFiles = false;
    LgsLogLevel logLevel = LGS_INFO;

    LgsConfigs() {
        setOS();
        init();
    }
    void init();
    LgsConfigs(const LgsConfigs&) = delete;
    LgsConfigs& operator=(const LgsConfigs&) = delete;
    void setOS();
};

inline void LgsConfigs::init() {
    const char* env = std::getenv("LGS_DEV_MODE");
    if (!env) return;
    isDevMode = std::string(env) == "1" || std::string(env) == "true";
}

inline void LgsConfigs::setOS() {
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

inline LgsConfigs lgsConfigs;
