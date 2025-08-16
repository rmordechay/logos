#pragma once
#include "LgsPaths.h"
#include <llvm/Target/TargetMachine.h>

class LgsFile;
class LgsCodeGen;

class LgsLinker {
public:
    const LgsPaths& paths;
    std::vector<LgsFile*> files;
    const char* linkString = "clang++ %s -L%s -llgs_runtime -o %s";

    LgsLinker(const LgsPaths& paths, const std::vector<LgsFile*>& modules) : paths(paths), files(modules) {}
    bool generateObjFile(std::unique_ptr<Module> mainModule, TargetMachine* targetMachine) const;
    bool link() const;
    ~LgsLinker() = default;
};

