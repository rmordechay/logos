#pragma once
#include "LgsEnv.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "Platform.h"
#include "extern/LgsCLang.h"
#include "types/LgsAny.h"

class LgsModule;
class LgsStrConst;
class LgsFile;
class LgsEnvFile;
class LgsObject;
class LgsFuncType;
class ThreadPool;
class LgsEnv;
class LgsAppFile;
class LgsMainFile;
struct LgsError;
struct LgsPaths;
struct RequireEnvVar;

class LgsApp final {
public:
    string name;
    string version;
    LgsPaths paths;
    LgsEnv activeEnv;
    vector<char*> args;
    LgsSymbolTable globals;
    vector<LgsFile*> files;
    LgsErrHandler errHandler;
    vector<LgsStrConst*> externFiles;
    LgsAppFile* appFile = nullptr;
    vector<LgsEnvFile*> envFiles;
    map<string, LgsModule*> modules;
    LgsCLang lgsCLang;

    explicit LgsApp(const path& rootDirPath = "") : lgsCLang(paths) {
        initPaths(rootDirPath);
    }

    void run();
    void initPaths(const path& rootDirPath);
    bool validate();
    bool parse();
    bool analyse();
    void initBuildDir() const;
    bool generate();
    bool link() const;
    void parseSrcFile(const string& codeText, path filePath = "");
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool resolveExternalFiles();
    bool resolveGlobalTypes();
    void setEnvVars();
    void setupActiveEnv();
    void loadBuiltins();
    void loadEnvFiles();
    void checkRequiredEnvVars();
    void handleExitWithErrors() const;
    ~LgsApp();
};
