#pragma once
#include "LgsApp.h"

class Logos {
public:
    LgsApp app;
    vector<char*> args;

    explicit Logos(const path& rootDirPath = "") {
        app.initPaths(rootDirPath);
    }
    void run();
    ~Logos() = default;
};