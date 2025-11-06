#pragma once
#include "logos/LgsPaths.h"
#include <vector>

namespace llvm {
    class Module;
    class TargetMachine;
}
struct LgsAppConfigs;
class LgsFile;
class LgsLLVMGen;

class LgsLinker {
public:
    LgsPaths& paths;
    LgsAppConfigs& appConfigs;
    std::vector<LgsFile*> files;
    std::vector<std::string> externalLibs;

    LgsLinker(LgsAppConfigs& appConfigs, LgsPaths& paths, const std::vector<LgsFile*>& modules) : paths(paths), appConfigs(appConfigs), files(modules) {}
    bool link() const;
};

