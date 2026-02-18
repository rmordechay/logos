#pragma once
#include <string>

#define LGS_BIG_SIZE_THRESHOLD 4
#define LGS_STR_BUFFER_SIZE 1024
#define LGS_MAX_LEVEL 1024*10
#define LGS_ITER_INIT_CAP 3
#define LGS_OBJ_MD_SIZE sizeof(size_t) + sizeof(void*)

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
    bool isTestMode = false;
    bool writeIRFiles = false;
    bool printIR = true;
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
    const char* env = getenv("LGS_DEV_MODE");
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
