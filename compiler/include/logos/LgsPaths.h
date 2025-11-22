#pragma once
#include <filesystem>

namespace fs = std::filesystem;

struct LgsPaths {
    fs::path rootPath;
    fs::path srcDir;
    fs::path envsDir;
    fs::path buildDir;
    fs::path buildDirIR;
    fs::path buildDirObjs;
    fs::path cacheFile;
    fs::path appConfigFile;
    fs::path execFile;
    fs::path cLibHeadersDir;
    fs::path lgsRootDir;
    fs::path lgsPackagesDir;
    fs::path cblasDir;
    void findLgsRootDir();
    void findCLibHeaders();
};
