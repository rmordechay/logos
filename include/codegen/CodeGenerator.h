#pragma once
#include "logos/Platform.h"

class LgsApp;

class CodeGenerator {
public:
    static void init(const LgsPaths& paths);
    static void writeIRToFile(map<string, Module*>& IRModules, LgsPaths& paths);
    ~CodeGenerator() = default;
};


