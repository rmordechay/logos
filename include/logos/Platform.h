#pragma once
#include "LgsDefinitions.h"
#include "configs/PlatformData.h"

struct Platform {
    bool (*link)(ArrayRef<const char*>, raw_ostream&, raw_ostream&, bool, bool) = LINK_FUNC;
};

struct LgsPaths {
    path rootDir;
    path rootDirAbs;
    path srcDir;
    path envsDir;
    path buildDir;
    path buildIR;
    path debugFile;
    path clibRoot;
    path clibInclude;
    path appFilePath;
    path objFilePath;
    path execFilePath;
    void initPaths(const path& rootDirPath);
};

inline void LgsPaths::initPaths(const path& rootDirPath) {
    if (rootDirPath == "") return;
    rootDir = rootDirPath;
    rootDirAbs = canonical(rootDir);
    srcDir = rootDir / LOGOS_SRC_DIR;
    envsDir = rootDir / LOGOS_ENVS_DIR;
    buildDir = rootDir / LOGOS_BUILD_DIR;
    buildIR = buildDir / LOGOS_BUILD_IR;
    debugFile = buildDir / LOGOS_DEBUG_FILE;
    objFilePath = buildDir / LOGOS_OBJECT_FILE;
    execFilePath = buildDir / LOGOS_EXECUTABLE_FILE;
    appFilePath = rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
    clibRoot = CLIB_ROOT;
    clibInclude = clibRoot / "usr/include";
}

inline Platform platform;
