#ifndef LOGOSCONFIGS_H
#define LOGOSCONFIGS_H
#include <llvm/Support/CodeGen.h>
#include <llvm/TargetParser/Host.h>

const auto LOGOS_THIS = "this";
const auto LOGOS_MAIN_FILE = "Main";
const auto LOGOS_MAIN_FUNCTION = "main";
const auto LOGOS_EXTENSION = ".lgs";
const auto LOGOS_BUILD_DIR = "../project/build/";
const auto OBJECT_FILE_PATH = "../project/build/output.o";
const auto EXECUTABLE_PATH = "../project/build/output";
const auto LOGOS_LIB_IR_FILE = "../stdlib/logoslib.ll";
constexpr auto IR_OBJECT_FILE = CodeGenFileType::ObjectFile;

#endif //LOGOSCONFIGS_H
