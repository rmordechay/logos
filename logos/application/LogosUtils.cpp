#include "LogosUtils.h"

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Target/TargetMachine.h>
#include "llvm/Support/FileSystem.h"

using namespace std;

bool Utils::isLogosFile(const filesystem::directory_entry& filePath) {
    return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
}

bool Utils::isMainFile(const filesystem::directory_entry& filePath) {
    return filePath.path().stem().string() == LOGOS_MAIN_FILE;
}

Module* Utils::createLLVMModuleFromFile(const string& filePath, LLVMContext& context, const TargetMachine& tm) {
    SMDiagnostic err;
    auto module = parseIRFile(filePath, err, context);
    module->setDataLayout(tm.createDataLayout());
    return module.release();
}

void Utils::emitLLVMFile(const string& filePath, const Module* const module) {
    error_code EC;
    raw_fd_ostream textFile(filePath, EC, sys::fs::OF_None);
    module->print(textFile, nullptr);
}

