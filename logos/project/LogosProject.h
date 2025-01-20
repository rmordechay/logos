#ifndef PROJECT_H
#define PROJECT_H
#include "CodeGenerator.h"
#include "AntlrConverter.h"
#include "LogosLexer.h"
#include "LogosPackage.h"
#include "SemaAnalyser.h"

#include <queue>
#include <thread>
#include <string>
#include "LogosUtils.h"
#include <thread>

using namespace std;

class LogosProject {
public:
    string rootPath;
    CodeGenerator* codeGenerator;
    AntlerConverter* antlerConverter;
    SemaAnalyser* semaAnalyser;

    explicit LogosProject(const string& rootPath) :
        rootPath(rootPath),
        codeGenerator(new CodeGenerator()),
        antlerConverter(new AntlerConverter()),
        semaAnalyser(new SemaAnalyser()) {
    }

    void runLogos();
    LogosPackage* getPackage(const filesystem::path& path);
    LogosFile* getFile(const filesystem::path& dirPath) const;
    static LogosParser* parseFile(const string& codeText);
    static string getCodeText(const filesystem::path& path);
    ~LogosProject();
};

#endif // PROJECT_H
