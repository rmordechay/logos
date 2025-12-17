#pragma once

#define LGS_SRC_DIR "src"
#define LGS_CODE_DIR "code"
#define LGS_ENVS_DIR "envs"
#define LGS_ROOT_DIR ".logos"
#define LGS_PACKAGES_DIR "packages"
#define LGS_BUILD_DIR "build"
#define LGS_BUILD_IR_DIR "IR"
#define LGS_BUILD_OBJECTS_DIR "objects"
#define LGS_FILE_EXTENSION ".lgs"
#define LGS_PREFIX "Lgs_"
#define LGS_CORO_SUFFIX "_co"
#define LGS_FILES_CACHE_FILE "metadata.bin"
#define LGS_MAIN_FILE "main.lgs"
#define LGS_APP_FILE_NAME "app.lgs"
#define LGS_DEBUG_CONFIG_FILE "logosdbg.bc"
#define LGS_DEFAULT_EXEC_FILE "out"
#define LGS_TYPEINFO_PREFIX "RTI_"
#define LGS_C "C"
#define LGS_MAIN_FUNC "main"
#define LGS_SELF "self"
#define LGS_LAMBDA_NAME "Lambda"
#define LGS_LAMBDA_IT_PARAM "it"
#define LGS_NULL_LITERAL "null"
#define LGS_UNKNOWN_TYPE "<Unknown>"
#define MSG_PLACEHOLDER "%s"
#define LGS_STR_FMT_PLACEHOLDER "<!v!>"
#define LGS_EMPTY_STR "\"\""

#define BLOCK_ENTRY "entry"
#define BLOCK_IF_TRUE "if_true"
#define BLOCK_IF_FALSE "if_false"
#define BLOCK_IF_EXIT "if_exit"
#define BLOCK_ELSE_IF "else_if"
#define BLOCK_ELSE_IF_CHECK "else_if_check"
#define BLOCK_EXIT_PATTERN "exit_switch"
#define BLOCK_CASE_PREFIX "case_"
#define BLOCK_LOOP_COND "loop_cond"
#define BLOCK_LOOP_BODY "loop_body"
#define BLOCK_LOOP_EXIT "loop_exit"

#define LGS_MSG_LINE_SEPERATOR "\n\n──────\n\n"
#define LGS_MSG_COLOR_RED "\033[1;31m"
#define LGS_MSG_COLOR_YELLOW "\033[1;33m"
#define LGS_MSG_COLOR_WHITE "\033[1;37m"
#define LGS_MSG_COLOR_RESET "\033[0m"
#define LGS_COLORIZE(text, color) color text LGS_MSG_COLOR_RESET
#define LGS_ERROR_TEXT "Error: "
#define LGS_WARNING_TEXT "Warning: "
#define LGS_PADDING_SIZE std::strlen(LGS_ERROR_TEXT)
#define LGS_ERROR_PADDING '\n' + std::string(LGS_PADDING_SIZE, ' ')


#if defined(_WIN32)
#include <windows.h>
#define LGS_LIB_NAME "liblgs.dll"
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#define LGS_LIB_NAME "liblgs.dylib"
#elif defined(__linux__)
#include <unistd.h>
#include <limits.h>
#define LGS_LIB_NAME "liblgs.so"
#else
    assert(0);
#endif

#define nakedf __attribute__((naked))
#define weakf __attribute__((weak))
