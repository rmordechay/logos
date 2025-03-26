#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include "json/json.hpp"

class CodeGenerator;
class LgsStack;

using namespace nlohmann;
using namespace std;

#define LOGOS_EXTENSION ".lgs"
#define LOGOS_SRC_DIR "src"
#define LOGOS_BUILD_DIR "build"
#define LOGOS_MAIN_FILE "Main"
#define LOGOS_MAIN_FUNC "main"
#define LOGOS_SELF "self"
#define OBJECT_FILE "output.o"
#define EXECUTABLE_FILE "output"

#if defined(_WIN32)
    #define OS_NAME "Windows"
    #define DEFAULT_LINKER "lld-link.exe"
    #define LIB_ROOT "C:/Program Files (x86)/Microsoft SDKs"
    #define ENTRY_POINT "main"
    #define PLATFORM_VERSION "10.0"  // Example Windows version
#elif defined(__linux__)
    #define OS_NAME "Linux"
    #define DEFAULT_LINKER "ld"
    #define LIB_ROOT "/usr/lib"
    #define ENTRY_POINT "_start"
    #define PLATFORM_VERSION "5.15"  // Example Linux kernel version
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_NAME "macos"
    #define DEFAULT_LINKER "ld.lld"
    #define LIB_ROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
    #define ENTRY_POINT "_main"
    #define PLATFORM_VERSION "15.0"
#elif defined(__unix__)
    #define OS_NAME "Unix"
    #define DEFAULT_LINKER "ld"
    #define LIB_ROOT "/usr/lib"
    #define ENTRY_POINT "_start"
    #define PLATFORM_VERSION "1.0"  // Generic Unix version
#else
    #define OS_NAME "Unknown OS"
    #define DEFAULT_LINKER "unknown_linker"
    #define LIB_ROOT "/unknown"
    #define ENTRY_POINT "unknown"
    #define PLATFORM_VERSION "0.0"
#endif

#if defined(__x86_64__) || defined(_M_X64)
    #define ARCH_NAME "x86_64 (64-bit)"
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCH_NAME "x86 (32-bit)"
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define ARCH_NAME "arm64"
#elif defined(__arm__) || defined(_M_ARM)
    #define ARCH_NAME "ARM (32-bit)"
#else
    #define ARCH_NAME "Unknown Architecture"
#endif


#endif //LOGOSMETADATA_H
