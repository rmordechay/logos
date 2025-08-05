#pragma once

#define NEW_LINE "\n"

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
    #define OS_NAME "Linux"
    #define CLIB_ROOT "/usr/lib/aarch64-linux-gnu/"
    #define CLIB_INCLUDE "/usr/include/aarch64-linux-gnu/bsd"
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_NAME "macOS"
    #define CLIB_ROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk"
    #define CLIB_INCLUDE "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include"
#elif defined(_WIN32)
    LLD_HAS_DRIVER(coff);
    #define OS_NAME "Win"
    #define CLIB_ROOT ""
#endif
