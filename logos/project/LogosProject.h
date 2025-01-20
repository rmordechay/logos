#ifndef PROJECT_H
#define PROJECT_H
#include "CodeGenerator.h"
#include "AntlrConverter.h"
#include "LogosLexer.h"
#include "SemaAnalyser.h"

#include <string>

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
    LogosRootPackage* getRootPackage();
    LogosPackage* getPackage(const filesystem::path& path);
    LogosFile* getFile(const filesystem::path& dirPath) const;
    static LogosParser* parseFile(const string& codeText);
    static string getCodeText(const filesystem::path& path);
    ~LogosProject();

    static bool isLogosFile(const std::filesystem::directory_entry& filePath) {
        return filePath.is_regular_file() && filePath.path().extension().string() == LOGOS_EXTENSION;
    }

    static bool isMainFile(const std::filesystem::directory_entry& filePath) {
        return filePath.path().stem().string() == LOGOS_MAIN_FILE;
    }
};

#endif // PROJECT_H
