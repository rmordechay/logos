#pragma once

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
    string arch;
    string platformVersion;
    path clibRoot;
    path inputFile;
    path outputFile;
    vector<const char*> linkerOpts;
    bool (*link)(ArrayRef<const char*>, raw_ostream&, raw_ostream&, bool, bool);
};

inline LgsPaths paths;
inline Platform platform;
