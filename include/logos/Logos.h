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
        application.paths.initPaths(rootDirPath);
        application.platform.setPlatform();
    }
    void run();
    ~Logos() = default;
};


