#ifndef PROJECT_H
#define PROJECT_H

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

class Application {
public:
    string rootPath;
    LogosLinker linker;
    LogosMainFile* mainFile = nullptr;
    std::mutex mtx;

    explicit Application(const string& rootPath) : rootPath(rootPath) {}
    void runLogos();
    map<string, LogosFile*> parseFiles();
    void parseTree(const string& path, map<string, LogosFile*>& files, ThreadPool& threadPool);
    static map<string, LogosSymbol> getGlobalsSymbols(const map<string, LogosFile*>& files);
    static LogosFile* getFile(const directory_entry&);
    bool analyse(const map<string, LogosFile*>& files, const map<string, LogosSymbol>& globalSymbols);
    ~Application() = default;
};

#endif // PROJECT_H
