#pragma once
#include "LgsModule.h"
#include "Platform.h"

#include <map>

class LgsLinker {
public:
    static bool link(const LgsPaths& paths, const map<string, LgsModule*>& modules);
    static bool generateObjFile(const LgsPaths& paths, Module* module);
    ~LgsLinker() = default;
};
