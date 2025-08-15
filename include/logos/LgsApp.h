#pragma once
#include "LgsEnv.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "LogosParser.h"
#include "lgsc/LgsCLang.h"
#include "utils/ThreadPool.h"

class LgsCodeGen;
class LgsStrConst;
class LgsFile;
class LgsEnvFile;
class LgsObject;
class LgsFuncType;
class ThreadPool;
class LgsEnv;
class LgsAppFile;
class LgsMainFile;
struct LgsBaseError;
struct LgsPaths;
struct RequireEnvVar;

class LgsApp final {
public:
    std::string name = "main";
    std::string version;
    LgsPaths paths;
    std::vector<LgsFile*> files;
    std::vector<char*> args;
    LgsSymbolTable globals;
    LgsErrHandler errHandler;
    std::vector<LgsEnvFile*> envFiles;
    LgsEnv activeEnv;
    LgsAppFile* appFile = nullptr;
    std::mutex mtx;
    ThreadPool threadPool;
    TargetMachine* targetMachine = nullptr;

    explicit LgsApp(const fs::path& rootDirPath = "") {
        paths.initPaths(rootDirPath);
    }

    void run();
    bool validate();
    bool parse();
    bool analyse();
    bool generate();
    bool link() const;
    void initBuild();
    void parseSrcFile(const std::string& codeText, fs::path filePath = "");
    bool checkParserErrors(LogosParser* parser);
    void parseEnvFile(fs::path fileEntry);
    void parseAppFile(fs::path fileEntry);
    bool resolveGlobalTypes();
    void loadBuiltins();
    void loadEnvFiles();
    void setEnvVars();
    void checkRequiredEnvVars();
    void writeIRFiles();
    void exitWithErrors() const;
    void setTargetMachine();
    ~LgsApp();
};
