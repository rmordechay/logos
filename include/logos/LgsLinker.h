#pragma once
#include "Platform.h"


class LgsModule;

class LgsLinker {
public:
    const LgsPaths& paths;
    map<string, LgsModule*> modules;

    LgsLinker(const LgsPaths& paths, const map<string, LgsModule*>& modules) : paths(paths), modules(modules) {}
    bool generateObjFile(unique_ptr<Module> mainModule) const;
    bool link() const;
    bool writeIRFiles() const;
    static bool validateModule(const Module* module);
    ~LgsLinker() = default;
};

