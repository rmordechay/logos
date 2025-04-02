#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <thread>
#include <filesystem>

#include "SemaAnalyser.h"
#include "ProjectAnalyser.h"

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

class Logos {
public:
    mutex mtx;
    path rootDir;
    path buildDir;
    path objFilePath;
    path execFilePath;
    vector<LgsError> errors;

    Logos() = default;
    explicit Logos(const path& rootDirPath) : rootDir(rootDirPath) {
        buildDir = rootDir / LOGOS_BUILD_DIR;
        objFilePath = buildDir / LOGOS_BUILD_DIR;
        execFilePath = buildDir / LOGOS_BUILD_DIR;
    }

    void run();
    void generateCode(const LgsMainFile* mainFile) const;
    void validateProject() const;
    vector<LgsFile*> parseFiles();
    LgsFile* parseFile(const directory_entry&) const;
    LgsFile* parseFile(const string& codeText, path absFilePath = "") const;
    void parseTree(const string& path, vector<LgsFile*>& files, ThreadPool& threadPool);
    void loadBuiltins() const;
    bool analyse(const vector<LgsFile*>& files);
    LgsMainFile* getMainFile(const vector<LgsFile*>& files) const;
    bool isLogosFile(const directory_entry& filePath) const;
    ~Logos() = default;
};

#endif // PROJECT_H
