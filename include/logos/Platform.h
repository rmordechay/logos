#pragma once
#include "data/LgsDefinitions.h"
#include "utils/LgsLogger.h"

struct Platform {
    string osName;
    string linker;
    string arch;
    string platformVersion;
    DataLayout dataLayout;
    vector<const char*> linkerOpts;
    bool (*link)(ArrayRef<const char*>, raw_ostream&, raw_ostream&, bool, bool);

    void setPlatform() {
        osName = OS_NAME;
        linker = LINKER;
        platformVersion = PLATFORM_VERSION;
        arch = ARCH_NAME;
        linkerOpts = LINKER_OPTS;
        link = LINK_FUNC;
    }
};

struct LgsPaths {
    path rootDir;
    path rootDirAbs;
    path srcDir;
    path envsDir;
    path buildDir;
    path clibRoot;
    path appFilePath;
    path objFilePath;
    path execFilePath;

    void initPaths(const path& rootDirPath) {
        if (rootDirPath == "") return;
        rootDir = rootDirPath;
        rootDirAbs = canonical(rootDir);
        srcDir = rootDir / LOGOS_SRC_DIR;
        envsDir = rootDir / LOGOS_ENVS_DIR;
        buildDir = rootDir / LOGOS_BUILD_DIR;
        objFilePath = buildDir / LOGOS_OBJECT_FILE;
        execFilePath = buildDir / LOGOS_EXECUTABLE_FILE;
        appFilePath = rootDir / LOGOS_APP_FILE_NAME LOGOS_FILE_EXTENSION;
        clibRoot = CLIB_ROOT;
    }
};

struct LgsApp {
    string name;
    LgsPaths paths;
    Platform platform;
    LogLevel logLevel = INFO;
};

inline LgsApp application;
