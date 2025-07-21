#pragma once
#include "logos/Platform.h"

class LgsModule;
class LgsApp;

class CodeGenerator {
public:
    static void initLLVM();
    static void writeIRToFile(map<string, LgsModule*>& modules, LgsPaths& paths);
    ~CodeGenerator() = default;
};


