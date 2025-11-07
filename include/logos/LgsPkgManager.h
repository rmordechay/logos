#pragma once
#include "LgsPaths.h"
#include <filesystem>

class LgsPkgManager {
public:
    LgsPaths paths;
    fs::path lgsRoot;
    void install();
};
