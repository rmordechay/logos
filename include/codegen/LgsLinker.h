#pragma once
#include "logos/LgsPaths.h"
#include <llvm/Passes/OptimizationLevel.h>
#include <vector>
namespace llvm {
    class Module;
    class TargetMachine;
}
struct LgsAppConfigs;
class LgsFile;
class LgsLLVMGen;

const auto LINK_STRING = "clang++ -flto %s -L%s -llgs -Wl,-rpath,%s -o %s";

class LgsLinker {
public:
    LgsPaths& paths;
    std::vector<LgsFile*> files;
    LgsAppConfigs& appConfigs;

    LgsLinker(LgsAppConfigs& appConfigs, LgsPaths& paths, const std::vector<LgsFile*>& modules) : paths(paths), files(modules), appConfigs(appConfigs) {}
    bool generateObjFile(std::unique_ptr<llvm::Module> mainModule, llvm::TargetMachine* targetMachine) const;
    std::string findLgsLib();
    bool link();
    llvm::OptimizationLevel getOptLevel(uint8_t level) const;
};

