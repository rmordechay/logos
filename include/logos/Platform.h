#pragma once
#include "data/LgsDefinitions.h"

struct Platform {
    string osName = OS_NAME;
    string linker = LINKER;
    string arch = ARCH_NAME;
    string platformVersion = PLATFORM_VERSION;
    vector<const char*> linkerOpts = LINKER_OPTS;
    bool (*link)(ArrayRef<const char*>, raw_ostream&, raw_ostream&, bool, bool) = LINK_FUNC;
    DataLayout dataLayout;
};

struct LgsPaths {
    path rootDir;
    path rootDirAbs;
    path srcDir;
    path envsDir;
    path buildDir;
    path clibRoot;
    path clibInclude;
    path appFilePath;
    path objFilePath;
    path execFilePath;
};

inline Platform platform;
