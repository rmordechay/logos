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
    fs::path cLibRoot;
    fs::path cLibHeadersDir;
    void initPaths();
    void findCLibRoot();
    void findCLibHeaders();
};
