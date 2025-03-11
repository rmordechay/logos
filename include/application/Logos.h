#ifndef PROJECT_H
#define PROJECT_H

#include "ProjectAnalyser.h"

#include <string>
#include <thread>
#include <filesystem>
#include "SemaAnalyser.h"
#include <LogosLinker.h>

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

class Logos {
public:
    std::mutex mtx;
    string rootPath;
    string srcPath;
    LogosLinker linker;

    explicit Logos(const string& rootPath) : rootPath(rootPath) {
        srcPath = rootPath + "/src";
    }

    void run();
    vector<LogosFile*> parseFiles();
    bool analyse(const vector<LogosFile*>& files, const map<string, LogosSymbol>& globalSymbols);
    void validateProject() const;
    void parseTree(const string& path, vector<LogosFile*>& files, ThreadPool& threadPool);
    LogosFile* parseFile(const directory_entry&);
    static void exitWithMessage(const string& errMsg);
    static LogosMainFile* getMainFile(const vector<LogosFile*>& files);
    static map<string, LogosSymbol> getGlobalsSymbols(const vector<LogosFile*>& files);
    static bool isLogosFile(const directory_entry& filePath);
    ~Logos() = default;
};

#endif // PROJECT_H
