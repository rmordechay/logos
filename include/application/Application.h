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
    SemaAnalyser semaAnalyser;
    LogosLinker linker;
    mutex mtx;

    explicit Application(const string& rootPath) : rootPath(rootPath) {}
    void runLogos();
    map<string, LogosFile*> parse();
    void parseTree(const string& path, map<string, LogosFile*>& files, ThreadPool& threadPool);
    static LogosFile* getFile(const directory_entry&);
    ~Application() = default;
};

#endif // PROJECT_H
