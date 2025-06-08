#pragma once

#include "logos/LgsProject.h"

struct LgsPaths;
using namespace llvm;
using namespace std;

class LgsLinker {
public:
    bool link(LogosProject& project) const;
    bool generateObjFile(Module* module, const string& path) const;
    ~LgsLinker() = default;
};


