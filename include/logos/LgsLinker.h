#pragma once
#include "LgsModule.h"
#include "Platform.h"

#include <map>

class LgsLinker {
public:
    bool link(const LgsPaths& paths, const map<string, LgsModule*>& modules) const;
    bool generateObjFile(const LgsPaths& paths, Module* module) const;
    ~LgsLinker() = default;
};
