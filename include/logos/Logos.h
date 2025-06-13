#pragma once
#include "LgsProject.h"
#include "Platform.h"

class Logos {
public:
    LgsProject project;
    vector<char*> args;

    explicit Logos(const path& rootDirPath = "") {
        application.paths.initPaths(rootDirPath);
        application.platform.setPlatform();
    }
    void run();
    ~Logos() = default;
};


