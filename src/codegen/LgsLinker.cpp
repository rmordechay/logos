#include "codegen/LgsLinker.h"
#include "codegen/LgsLLVMGen.h"
#include "logos/LgsAppConfigs.h"
#include <llvm/Passes/PassBuilder.h>
#include "llvm/Bitcode/BitcodeWriter.h"
#include <llvm/Support/FileSystem.h>

bool LgsLinker::link() const {
    LLVMContext context;
    std::unique_ptr<Module> mainModule = nullptr;
    std::vector<std::unique_ptr<Module>> modules;
    const auto lgsLibPath = findLgsLib();
    std::string objFileList;
    for (const auto& objPath : fs::directory_iterator(paths.buildDirObjs)) {
        objFileList += objPath.path().string() + " ";
    }
    char linkCmd[2048];
    std::snprintf(
        linkCmd,
        sizeof(linkCmd),
        LINK_STRING,
        objFileList.c_str(),
        lgsLibPath.c_str(),
        lgsLibPath.c_str(),
        paths.execFilePath.c_str()
    );
    return std::system(linkCmd) == 0;
}

std::string LgsLinker::findLgsLib() const {
#ifdef __APPLE__
        return paths.rootPath.parent_path() / "cmake-build-debug";
#elif defined(__linux__)
        return paths.rootPath.parent_path() / "build";
#endif
}

llvm::OptimizationLevel LgsLinker::getOptLevel(const LgsAppConfigs& appConfigs, const uint8_t level) {
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O0;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O1;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O2;
    if (appConfigs.optLevel == level) return llvm::OptimizationLevel::O3;
    assert(0);
}
