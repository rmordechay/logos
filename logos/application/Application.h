#ifndef PROJECT_H
#define PROJECT_H
#include "CodeGenerator.h"
#include "AntlrConverter.h"
#include "LogosLexer.h"
#include "SemaAnalyser.h"

#include <queue>
#include <thread>
#include <string>
#include "LogosUtils.h"

#include <future>
#include <thread>

using namespace std;

class Application {
public:
    string rootPath;
    CodeGenerator* codeGenerator;
    AntlerConverter* antlerConverter;
    SemaAnalyser* semaAnalyser;

    explicit Application(const string& rootPath) :
        rootPath(rootPath),
        codeGenerator(new CodeGenerator()),
        antlerConverter(new AntlerConverter()),
        semaAnalyser(new SemaAnalyser()) {
    }

    void runLogos();
    void flattenTree(const filesystem::path& path, vector<future<LogosFile*>>& files);
    future<LogosFile*> getFile(const filesystem::path& path) const;
    ~Application();
};

#endif // PROJECT_H
