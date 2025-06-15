#pragma once

#define LOGOS_FILE_EXTENSION ".lgs"
#define LOGOS_SRC_DIR "src"
#define LOGOS_ENVS_DIR "envs"
#define LOGOS_BUILD_DIR "build"
#define LOGOS_MAIN_FILE_NAME "Main"
#define LOGOS_APP_FILE_NAME "App"
#define LOGOS_MAIN_FUNC "main"
#define LOGOS_SELF "self"
#define LOGOS_OBJECT_FILE "main.o"
#define LOGOS_EXECUTABLE_FILE "output"
#define LOGOS_STR_FORMAT_PART "%v"
#define LOGOS_DEFAULT_ENUM "DEFAULT"
#define CLANG_BINARY "clang"
#define ERROR_STR "\033[1;31mError:\033[0m "

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

#if defined(__linux__)
    LLD_HAS_DRIVER(elf);
    #define OS_NAME "Linux"
    #define LINKER "ld"
    #define CLIB_ROOT "/usr/lib/aarch64-linux-gnu/"
    #define PLATFORM_VERSION "15.0"
    #define LINK_FUNC lld::elf::link
    #define LINKER_OPTS { \
        LINKER, \
        "-L", "/usr/lib/aarch64-linux-gnu", \
        "../stdlib/lgslib.a", \
        "-lc", \
        "--dynamic-linker", "/lib/ld-linux-aarch64.so.1", \
        "/usr/lib/aarch64-linux-gnu/crti.o", \
        "/usr/lib/aarch64-linux-gnu/crtn.o", \
    }
#elif defined(__APPLE__) && defined(__MACH__)
    LLD_HAS_DRIVER(macho);
    #define OS_NAME "macOS"
    #define LINKER "ld.lld"
    #define CLIB_ROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
    #define PLATFORM_VERSION "15.0"
    #define LINK_FUNC lld::macho::link
    #define LINKER_OPTS { \
        LINKER, \
        "-lSystem", \
        "-syslibroot", CLIB_ROOT, \
        "../stdlib/lgslib.a", \
        "-platform_version", OS_NAME, PLATFORM_VERSION, PLATFORM_VERSION, \
        "-arch", ARCH_NAME, \
    }
#elif defined(_WIN32)
    LLD_HAS_DRIVER(coff);
    #define OS_NAME "Win"
    #define LINKER ""
    #define CLIB_ROOT ""
    #define PLATFORM_VERSION ""
    #define LINK_FUNC lld::coff::link
#endif
