#pragma once
#include "extern/LgsCLang.h"
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
        paths.initPaths(rootDirPath);
        platform.setPlatform();
    }
    void run();
    ~Logos() = default;
};


