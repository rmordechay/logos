#pragma once

#include "logos/LgsProject.h"

struct LgsPaths;
using namespace llvm;


class LgsLinker {
public:
    bool link(LogosProject& project) const;
    bool generateObjFile(Module* module, const string& path) const;
    void setPlatform(const string& inputFile, const string& outputFile) const;
    ~LgsLinker() = default;
};


