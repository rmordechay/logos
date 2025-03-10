#ifndef LOGOSCONFIGS_H
#define LOGOSCONFIGS_H

const auto LOGOS_VERSION = "0.0.1";

// Logos
const auto LOGOS_EXTENSION = ".lgs";
const auto LOGOS_SRC_PATH = "src";
const auto LOGOS_BUILD_DIR = "build";
const auto LOGOS_MAIN_FILE_NAME = "Main";
const auto LOGOS_MAIN_FUNCT_NAME = "main";
const auto LOGOS_SELF = "self";

// LLVM
const auto OBJECT_FILE_PATH = "../project/build/output.o";
const auto EXECUTABLE_PATH = "../project/build/output";
const auto LOGOS_STDLIB = "../stdlib/logoslib.ll";
constexpr auto IR_OBJECT_FILE = llvm::CodeGenFileType::ObjectFile;

// Platform dependent constansts
#if defined(_WIN32)
    #define OS_NAME "Windows"
#elif defined(__linux__)
    #define OS_NAME "Linux"
#elif defined(__APPLE__) && defined(__MACH__)
    #define OS_NAME "MacOS"
#elif defined(__unix__)
    #define OS_NAME "Unix"
#else
    #define OS_NAME "Unknown OS"
#endif

#if defined(__x86_64__) || defined(_M_X64)
    #define ARCH_NAME "x86_64 (64-bit)"
#elif defined(__i386__) || defined(_M_IX86)
    #define ARCH_NAME "x86 (32-bit)"
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define ARCH_NAME "ARM64"
#elif defined(__arm__) || defined(_M_ARM)
    #define ARCH_NAME "ARM (32-bit)"
#else
    #define ARCH_NAME "Unknown Architecture"
#endif

#endif //LOGOSCONFIGS_H
