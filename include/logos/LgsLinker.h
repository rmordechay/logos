#pragma once
#include "LgsPaths.h"

namespace llvm {
    class Module;
    class TargetMachine;
}
class LgsFile;
class LgsCodeGen;

class LgsLinker {
public:
    const LgsPaths& paths;
    std::vector<LgsFile*> files;
    const char* linkString = "clang++ %s -L%s -llgs_runtime -o %s";

    LgsLinker(const LgsPaths& paths, const std::vector<LgsFile*>& modules) : paths(paths), files(modules) {}
    bool generateObjFile(std::unique_ptr<llvm::Module> mainModule, llvm::TargetMachine* targetMachine) const;
    bool link() const;
    ~LgsLinker() = default;
};

