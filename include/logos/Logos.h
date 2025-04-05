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
    path objFilePath;
    path execFilePath;
};

class Logos {
public:
    mutex mtx;
    vector<LgsError> errors;
    LgsPaths paths;

    explicit Logos(const path& rootDirPath) {
        initPaths(rootDirPath);
    }

    void run();
    void generateCode(const LgsMainFile* mainFile) const;
    LgsMainFile* getMainFile(const vector<LgsFile*>& files) const;
    bool analyse(const vector<LgsFile*>& files);
    void initPaths(const path& rootDirPath);
    void initLLVM() const;
    ~Logos() = default;
};

#endif // PROJECT_H
