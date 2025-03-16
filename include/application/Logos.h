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

    explicit Logos(const path& rootDirPath) : rootDir(rootDirPath) {
        buildDir = rootDir / LOGOS_BUILD_DIR;
        objFilePath = buildDir / LOGOS_BUILD_DIR;
        execFilePath = buildDir / LOGOS_BUILD_DIR;
    }
    void run();
    void generateCode(const LgsMainFile* mainFile, const map<string, LgsSymbol>& globalSymbols) const;
    void validateProject() const;
    vector<LgsFile*> parseFiles();
    LgsFile* parseFile(const directory_entry&) const;
    void parseTree(const string& path, vector<LgsFile*>& files, ThreadPool& threadPool);
    static void addBuiltinFuncs(map<string, LgsSymbol>& globalSymbols);
    bool analyse(const vector<LgsFile*>& files, const map<string, LgsSymbol>& globalSymbols);
    static LgsMainFile* getMainFile(const vector<LgsFile*>& files);
    static void setGlobalsSymbols(const vector<LgsFile*>& files, map<string, LgsSymbol>& globalSymbols);
    static bool isLogosFile(const directory_entry& filePath);
    static void exitWithMessage(const string& errMsg);
    ~Logos() = default;
};

#endif // PROJECT_H
