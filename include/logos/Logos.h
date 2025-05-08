#ifndef PROJECT_H
#define PROJECT_H
#include <filesystem>
#include "SemaAnalyser.h"
#include "LgsProject.h"

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

class Logos {
public:
    LogosProject project;
    vector<char*> args;
    vector<LgsError> errors;

    explicit Logos(const path& rootDirPath) {
        initPaths(rootDirPath);
    }
    void run();
    void initPaths(const path& rootDirPath) const;
    ~Logos() = default;
};

#endif // PROJECT_H
