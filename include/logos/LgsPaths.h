#pragma once

struct LgsPaths {
    fs::path rootPath;
    fs::path srcDir;
    fs::path envsDir;
    fs::path buildDir;
    fs::path buildIR;
    fs::path lgsStdlibDir;
    fs::path appFilePath;
    fs::path objFilePath;
    fs::path execFilePath;
    fs::path lgsRoot;
    fs::path cLibRoot;
    fs::path cLibHeadersDir;
    void initPaths();
    void findLgsRoot();
    void findCLibRoot();
    void findCLibHeaders();
};
