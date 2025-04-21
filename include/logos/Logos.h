#ifndef PROJECT_H
#define PROJECT_H
#include <thread>
#include <filesystem>
#include "SemaAnalyser.h"
#include "LogosProject.h"

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

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

inline LgsPaths paths;

class Logos {
public:
    mutex mtx;
    LogosProject project;
    vector<LgsError> errors;

    explicit Logos(const path& rootDirPath) {
        initPaths(rootDirPath);
    }

    void run();
    LgsMainFile* getMainFile(const vector<LgsFile*>& files) const;
    bool analyse(const vector<LgsFile*>& files);
    void initPaths(const path& rootDirPath) const;
    ~Logos() = default;
};

#endif // PROJECT_H
