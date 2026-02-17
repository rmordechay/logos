#pragma once
#include <filesystem>
#include <vector>

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
    fs::path testExecFile;
    fs::path lgsRootDir;
    fs::path lgsPackagesDir;
    fs::path cblasDir;
    fs::path cLibHeadersDir;
    std::vector<fs::path> userCLibs;
    std::vector<fs::path> userSearchPaths;
    void findLgsRootDir();
    void findCLibHeaders();
};
