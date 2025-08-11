#pragma once
#include "configs/LgsDefinitions.h"

struct LgsPaths {
    filesystem::path relRootDir;
    filesystem::path rootDir;
    filesystem::path srcDir;
    filesystem::path envsDir;
    filesystem::path buildDir;
    filesystem::path buildIR;
    filesystem::path lgsStdlibDir;
    filesystem::path appFilePath;
    filesystem::path objFilePath;
    filesystem::path execFilePath;
    void initPaths(const filesystem::path& rootDirPath);
};

inline void LgsPaths::initPaths(const filesystem::path& rootDirPath) {
    if (rootDirPath == "") return;
    relRootDir = rootDirPath;
    rootDir = canonical(rootDirPath);
    srcDir = rootDir / LOGOS_SRC_DIR;
    envsDir = rootDir / LOGOS_ENVS_DIR;
    buildDir = rootDir / LOGOS_BUILD_DIR;
    buildIR = buildDir / LOGOS_BUILD_IR;
    objFilePath = buildDir / LOGOS_OBJECT_FILE;
    execFilePath = buildDir / LOGOS_EXECUTABLE_FILE;
    appFilePath = rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
}
