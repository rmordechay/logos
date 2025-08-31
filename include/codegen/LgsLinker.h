#pragma once
#include "logos/LgsPaths.h"
#include <llvm/Passes/OptimizationLevel.h>

namespace llvm {
    class Module;
    class TargetMachine;
}
struct LgsAppConfigs;
class LgsFile;
class LgsLLVMGen;

const auto LINK_STRING = "clang++ %s -L%s -llgs_core -Wl,-rpath,%s -o %s";

class LgsLinker {
public:
    const LgsPaths& paths;
    std::vector<LgsFile*> files;
    LgsAppConfigs& appConfigs;

    LgsLinker(LgsAppConfigs& appConfigs, const LgsPaths& paths, const std::vector<LgsFile*>& modules) : appConfigs(appConfigs), paths(paths), files(modules) {}
    bool generateObjFile(std::unique_ptr<llvm::Module> mainModule, llvm::TargetMachine* targetMachine) const;
    bool link() const;
    llvm::OptimizationLevel getOptLevel(uint8_t level) const;
};

