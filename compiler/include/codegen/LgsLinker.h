#pragma once
#include <vector>
#include <string>

#include "logos/LgsPaths.h"

struct LgsPaths;

namespace llvm {
    class Module;
    class TargetMachine;
}
struct LgsAppConfigs;
class LgsFile;
class LgsCodeGen;

class LgsLinker {
public:
    LgsPaths& paths;
    LgsAppConfigs& appConfigs;
    std::vector<std::string> filesToLink;
    std::vector<std::string> importPaths;

    LgsLinker(LgsAppConfigs& appConfigs, LgsPaths& paths) : paths(paths), appConfigs(appConfigs) {}
    bool link() const;
};

