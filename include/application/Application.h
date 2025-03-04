#ifndef PROJECT_H
#define PROJECT_H

#include <string>
#include <thread>

#include "SemaAnalyser.h"
#include "LogosLinker.h"
#include "LogosUtils.h"

class ThreadPool;
using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

class Application {
public:
    string rootPath;
    LogosLinker linker;
    LogosMainFile* mainFile = nullptr;
    mutex mtx;

    explicit Application(const string& rootPath) : rootPath(rootPath) {}
    void runLogos();
    map<string, LogosFile*> parseFiles();
    void parseTree(const string& path, map<string, LogosFile*>& files, ThreadPool& threadPool);
    static map<string, LogosSymbol> collectGlobals(const map<string, LogosFile*>& files);
    static LogosFile* getFile(const directory_entry&);
    static void runBinary();
    ~Application() = default;
};

#endif // PROJECT_H
