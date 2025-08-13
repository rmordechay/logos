#pragma once
#include "LgsEnv.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "LgsRuntime.h"
#include "lgsc/LgsCLang.h"

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
    string name;
    string version;
    LgsPaths paths;
    LgsEnv activeEnv;
    LgsRuntime runtime;
    vector<char*> args;
    LgsSymbolTable globals;
    vector<LgsFile*> files;
    LgsErrHandler errHandler;
    vector<LgsEnvFile*> envFiles;
    LgsAppFile* appFile = nullptr;
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
    void parseSrcFile(const string& codeText, fs::path filePath = "");
    void parseEnvFile(fs::path fileEntry);
    void parseAppFile(fs::path fileEntry);
    bool resolveGlobalTypes();
    void loadBuiltins();
    void loadEnvFiles();
    void setEnvVars();
    void setupActiveEnv();
    void checkRequiredEnvVars();
    void writeIRFiles() const;
    void exitWithErrors() const;
    void setTargetMachine();
    ~LgsApp();
};
