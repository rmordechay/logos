#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H
#include <json/json.hpp>


class CodeGenerator;
class LgsStack;

using namespace std;
using namespace nlohmann;

#define LOGOS_FILE_EXTENSION ".lgs"
#define LOGOS_SRC_DIR "src"
#define LOGOS_ENVS_DIR "envs"
#define LOGOS_BUILD_DIR "build"
#define LOGOS_MAIN_FILE_NAME "Main"
#define LOGOS_APP_FILE_NAME "App"
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
    #define LINK_FUNC lld::elf::link(getLinkerOpts(), outs(), errs(), false, false);
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_NAME "macos"
    #define DEFAULT_LINKER "ld.lld"
    #define LIB_ROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
    #define ENTRY_POINT "_main"
    #define PLATFORM_VERSION "15.0"
    #define LINK_FUNC lld::macho::link(getLinkerOpts(), outs(), errs(), false, false);
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
