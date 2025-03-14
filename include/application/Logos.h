#ifndef PROJECT_H
#define PROJECT_H

#include "ProjectAnalyser.h"

#include <string>
#include <thread>
#include <filesystem>
#include "SemaAnalyser.h"
#include <LgsLinker.h>

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

class Logos {
public:
    mutex mtx;
    path rootDir;
    path srcDir;
    path buildDir;
    path objectFile;
    path execFile;

    explicit Logos(const path& rootPath) : rootDir(rootPath) {
        srcDir = rootPath / LOGOS_SRC_DIR;
        buildDir = rootPath / LOGOS_BUILD_DIR;
        objectFile = buildDir / OBJECT_FILE;
        execFile = buildDir / EXECUTABLE_FILE;
    }

    void run();
    vector<LgsFile*> parseFiles();
    bool analyse(const vector<LgsFile*>& files, const map<string, LgsSymbol>& globalSymbols);
    void validateProject() const;
    void parseTree(const string& path, vector<LgsFile*>& files, ThreadPool& threadPool);
    LgsFile* parseFile(const directory_entry&) const;
    static void exitWithMessage(const string& errMsg);
    static LgsMainFile* getMainFile(const vector<LgsFile*>& files);
    static map<string, LgsSymbol> getGlobalsSymbols(const vector<LgsFile*>& files);
    static bool isLogosFile(const directory_entry& filePath);
    ~Logos() = default;
};

#endif // PROJECT_H
