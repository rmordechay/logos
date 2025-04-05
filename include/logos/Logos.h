#ifndef PROJECT_H
#define PROJECT_H

#include "LgsEnvFile.h"

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

struct LgsPaths {
    path rootDir;
    path srcPath;
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
    void validateProject() const;
    vector<LgsFile*> parseFiles();
    vector<LgsFile*> parseEnvFiles();
    void parseTree(const string& path, vector<LgsFile*>& files, ThreadPool& threadPool);
    LgsFile* parseFile(const directory_entry&) const;
    LgsFile* parseFile(const string& codeText, path absFilePath = "") const;
    LgsEnvFile* parseEnvFile(path fileEntry) const;
    LgsMainFile* getMainFile(const vector<LgsFile*>& files) const;
    void loadBuiltins() const;
    bool analyse(const vector<LgsFile*>& files);
    void initPaths(const path& rootDirPath);
    void initLLVM() const;
    bool isLogosFile(const directory_entry& filePath) const;
    ~Logos() = default;
};

#endif // PROJECT_H
