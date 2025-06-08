#pragma once
#include <pch.h>

struct LgsPaths {
    path rootDir;
    path rootDirAbs;
    path srcDir;
    path envsDir;
    path buildDir;
    path appFilePath;
    path objFilePath;
    path execFilePath;
};

struct Platform {
    string osName;
    string linker;
    string libRoot;
    string arch;
    string platformVersion;
    string inputFile;
    string outputFile;
    vector<const char*> linkerOpts;
    bool (*link)(ArrayRef<const char*>, raw_ostream&, raw_ostream&, bool, bool);
};

inline LgsPaths paths;
inline Platform platform;
