#pragma once
#include "LgsEnv.h"
#include "LgsSymbolTable.h"
#include "utils/LgsErrHandler.h"
#include "LgsPaths.h"
#include "extern/LgsCLang.h"

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
    LgsEnv activeEnv;
    vector<char*> args;
    LgsSymbolTable globals;
    vector<LgsFile*> files;
    LgsErrHandler errHandler;
    vector<LgsStrConst*> externFiles;
    LgsAppFile* appFile = nullptr;
    vector<LgsEnvFile*> envFiles;
    LgsCLang lgsCLang;

    explicit LgsApp(const filesystem::path& rootDirPath = "") : lgsCLang(paths) {
        paths.initPaths(rootDirPath);
    }

    void run();
    bool validate();
    bool parse();
    bool analyse();
    bool generate() const;
    bool link() const;
    void parseSrcFile(const string& codeText, filesystem::path filePath = "");
    void parseEnvFile(filesystem::path fileEntry);
    void parseAppFile(filesystem::path fileEntry);
    bool resolveExternalFiles();
    bool resolveGlobalTypes();
    void loadBuiltins();
    void loadEnvFiles();
    void setEnvVars();
    void setupActiveEnv();
    void checkRequiredEnvVars();
    void writeIRFiles() const;
    void exitWithErrors() const;
    static void initBuild();
    ~LgsApp();
};
