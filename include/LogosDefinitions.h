#ifndef LOGOSCONFIGS_H
#define LOGOSCONFIGS_H
#include <llvm/Support/CodeGen.h>
#include <llvm/TargetParser/Host.h>

const auto LOGOS_SOURCE_PACKAGE = "root";
const auto LOGOS_MAIN_FILE = "Main";
const auto LOGOS_MAIN_FUNCTION = "main";
const auto LOGOS_EXTENSION = ".lgs";
const auto LOGOS_THIS = "this";
const auto LOGOS_BUILD_DIR = "../project/src/build/";
const auto LOGOS_LIB_IR_FILE = "LogosStdlib.ll";
const auto LINKED_OBJECT_FILE = "../output.o";
const auto LINKED_IR_FILE = "../output.ll";
constexpr auto IR_OBJECT_FILE = llvm::CodeGenFileType::ObjectFile;

#endif //LOGOSCONFIGS_H
