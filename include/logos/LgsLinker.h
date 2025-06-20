#pragma once
#include "Platform.h"

class LgsLinker {
public:
    bool link(const LgsPaths& paths, const map<string, Module*>& IRModules) const;
    bool generateObjFile(const LgsPaths& paths, Module* module) const;
    ~LgsLinker() = default;
};
