#pragma once
#include "extern/LgsC.h"
#include <filesystem>
#include "LgsProject.h"

struct LgsError;
class ThreadPool;
using namespace filesystem;

using namespace llvm;

class Logos {
public:
    LogosProject project;
    vector<char*> args;

    explicit Logos(const path& rootDirPath = "") {
        if (rootDirPath != "") initPaths(rootDirPath);
    }
    void run();
    void initPaths(const path& rootDirPath) const;
    ~Logos() = default;
};


