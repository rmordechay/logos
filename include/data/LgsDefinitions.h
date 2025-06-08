#ifndef LOGOSMETADATA_H
#define LOGOSMETADATA_H

#include <lld/Common/Driver.h>
class CodeGenerator;
class LgsRuntime;
using namespace std;
using namespace nlohmann;
using namespace llvm;

#define LOGOS_FILE_EXTENSION ".lgs"
#define LOGOS_SRC_DIR "src"
#define LOGOS_ENVS_DIR "envs"
#define LOGOS_BUILD_DIR "build"
#define LOGOS_MAIN_FILE_NAME "Main"
#define LOGOS_APP_FILE_NAME "App"
#define LOGOS_MAIN_FUNC "main"
#define LOGOS_SELF "self"
#define LOGOS_PARENT_OBJ "Object"
#define LOGOS_OBJECT_FILE "main.o"
#define LOGOS_EXECUTABLE_FILE "output"
#define LOGOS_STR_FORMAT_PART "%v"
#define LOGOS_LOOP_CONDITION "loop_condition"
#define LOGOS_LOOP_BODY "loop_body"
#define LOGOS_LOOP_EXIT "loop_exit"
#define ERROR_STR "\033[1;31mError:\033[0m "

#if defined(__linux__)
LLD_HAS_DRIVER(elf);
#elif defined(__APPLE__) && defined(__MACH__)
LLD_HAS_DRIVER(macho);
#elif defined(_WIN32)
LLD_HAS_DRIVER(coff);
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
