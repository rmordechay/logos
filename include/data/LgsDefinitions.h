#pragma once

#define LGS_FILE_EXTENSION ".lgs"
#define LGS_RUNTIME_NAMES_PREFIX "Lgs_"
#define LGS_SRC_DIR "src"
#define LGS_ENVS_DIR "envs"
#define LGS_BUILD_DIR "build"
#define LGS_BUILD_IR "IR"
#define LGS_MAIN_FILE_NAME "Main.lgs"
#define LGS_APP_FILE_NAME "App.lgs"
#define LGS_MAIN_FUNC_NAME "main"
#define LGS_SELF "self"
#define LGS_STR_FMT_PLACEHOLDER "$!v!$"
#define LGS_UNKNOWN_TYPE "<Unknown>"
#define LGS_ANONYMOUS_STR "anonymous"
#define LGS_NULL_LITERAL "null"

#define BLOCK_NAME_IF_TRUE "if_true"
#define BLOCK_NAME_IF_FALSE "if_false"
#define BLOCK_NAME_ELSE "else"
#define BLOCK_NAME_ELSE_IF "else_if"
#define BLOCK_NAME_ELSE_IF_CHECK "else_if_check"
#define BLOCK_NAME_EXIT_PATTERN "exit_switch"
#define BLOCK_NAME_CASE_PREFIX "case_"
#define BLOCK_NAME_ENTRY "entry"
#define BLOCK_NAME_LOOP_COND "loop_cond"
#define BLOCK_NAME_LOOP_BODY "loop_body"
#define BLOCK_NAME_LOOP_EXIT "loop_exit"
#define BLOCK_NAME_CLEANUP "cleanup"

#define LGS_MSG_LINE_SEPERATOR "\n\n------\n\n"
#define LGS_MSG_COLOR_RED "\033[1;31m"
#define LGS_MSG_COLOR_YELLOW "\033[1;33m"
#define LGS_MSG_COLOR_WHITE "\033[1;37m"
#define LGS_MSG_COLOR_RESET "\033[0m"
#define LGS_COLORIZE(text, color) color text LGS_MSG_COLOR_RESET
#define LGS_ERROR_TEXT "Error: "
#define LGS_ERROR_STR LGS_COLORIZE(LGS_ERROR_TEXT, LGS_MSG_COLOR_RED)
#define LGS_WARN_STR LGS_COLORIZE("Warning: ", LGS_MSG_COLOR_YELLOW)
#define LGS_PADDING_SIZE std::strlen(LGS_ERROR_TEXT)
#define LGS_ERROR_PADDING '\n' + std::string(LGS_PADDING_SIZE, ' ')
