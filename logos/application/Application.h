#ifndef PROJECT_H
#define PROJECT_H

#include <queue>
#include <string>
#include <thread>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>

#include "AntlrConverter.h"

using namespace filesystem;
using namespace std;
using namespace antlr4;
using namespace llvm;

#include "CodeGenerator.h"
#include "LogosLexer.h"
#include "SemaAnalyser.h"
#include "LogosUtils.h"

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
