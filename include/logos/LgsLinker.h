#pragma once
#include "LgsPaths.h"
#include <llvm/Target/TargetMachine.h>

class LgsFile;
class LgsCodeGen;

class LgsLinker {
public:
    const LgsPaths& paths;
    vector<LgsFile*> files;

    LgsLinker(const LgsPaths& paths, const vector<LgsFile*>& modules) : paths(paths), files(modules) {}
    bool generateObjFile(unique_ptr<Module> mainModule, TargetMachine* targetMachine) const;
    bool link(TargetMachine* targetMachine) const;
    ~LgsLinker() = default;
};

