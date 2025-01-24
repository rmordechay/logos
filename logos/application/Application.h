#ifndef PROJECT_H
#define PROJECT_H

#include <queue>
#include <thread>
#include <string>
#include <future>
#include <thread>
#include "CodeGenerator.h"
#include "AntlrConverter.h"
#include "LogosLexer.h"
#include "SemaAnalyser.h"
#include "LogosUtils.h"

using namespace filesystem;
using namespace std;
using namespace antlr4;

class Application {
public:
    string rootPath;
    CodeGenerator codeGenerator;
    SemaAnalyser semaAnalyser;
    mutex mtx;

    explicit Application(const string& rootPath) : rootPath(rootPath) {}
    void runLogos();
    vector<LogosFile*> parse();
    void flattenTree(const string& path, vector<LogosFile*>& files, ThreadPool& threadPool);
    static LogosFile* getFile(const directory_entry&);
    ~Application() = default;
};

#endif // PROJECT_H
