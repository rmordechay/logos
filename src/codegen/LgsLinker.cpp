#include "codegen/LgsLinker.h"
#include "codegen/LgsLLVMGen.h"
#include "logos/LgsAppConfigs.h"
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Support/FileSystem.h>

#define LINK_CMD_STRING "clang %s -L%s -llgs_runtime -Wl,-rpath,%s -o %s"

bool LgsLinker::link() const {
    assert(paths.lgsLibPath != "" && paths.execFilePath != "");
    std::string objFileList;
    for (const auto& objPath : fs::directory_iterator(paths.buildDirObjs)) {
        if (objPath.path().extension() == ".o") {
            objFileList += objPath.path().string() + " ";
        }
    }
    assert(objFileList != "");
    char cmd[1024*4];
    std::snprintf(
        cmd,
        sizeof(cmd),
        LINK_CMD_STRING,
        objFileList.c_str(),
        paths.lgsLibPath.c_str(),
        paths.lgsLibPath.c_str(),
        paths.execFilePath.c_str()
    );
    return std::system(cmd) == 0;
}

llvm::OptimizationLevel LgsLinker::getOptLevel(const LgsAppConfigs& appConfigs, const uint8_t level) {
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O0;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O1;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O2;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O3;
    assert(0);
}
