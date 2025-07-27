#pragma once
#include "data/PlatformData.h"

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
    path clibRoot;
    path clibInclude;
    path appFilePath;
    path objFilePath;
    path execFilePath;
};

inline Platform platform;
