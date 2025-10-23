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
    fs::path filesMetadata;
    fs::path lgsStdlibDir;
    fs::path appFilePath;
    fs::path objFilePath;
    fs::path execFilePath;
    fs::path cLibRoot;
    fs::path cLibHeadersDir;
    void initPaths();
    void findCLibRoot();
    void findCLibHeaders();
};
