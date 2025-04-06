#ifndef PROJECT_H
#define PROJECT_H

#include "LgsEnvFile.h"

#include <string>
#include <thread>
#include <filesystem>

#include "SemaAnalyser.h"
#include "LgsProject.h"

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

struct LgsPaths {
    path rootDir;
    path srcDir;
    path envsDir;
    path buildDir;
    path appFilePath;
    path objFilePath;
    path execFilePath;
};

class Logos {
public:
    mutex mtx;
    vector<LgsError> errors;
    LgsPaths paths;
    LgsProject project;

    explicit Logos(const path& rootDirPath) : project(LgsProject(&paths)) {
        initPaths(rootDirPath);
    }

    void run();
    LgsMainFile* getMainFile(const vector<LgsFile*>& files) const;
    bool analyse(const vector<LgsFile*>& files);
    void initPaths(const path& rootDirPath);
    ~Logos() = default;
};

#endif // PROJECT_H
