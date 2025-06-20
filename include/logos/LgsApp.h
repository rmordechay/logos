#pragma once
#include "LgsEnv.h"
#include "utils/LgsErrHandler.h"
#include "Platform.h"
#include "extern/LgsCLang.h"

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
    LgsCLang lgsCLang;
    vector<char*> args;
    LgsEnv activeEnv;
    vector<LgsFile*> files;
    vector<LgsStrConst*> externFiles;
    LgsErrHandler errHandler;
    vector<LgsEnvFile*> envFiles;
    map<string, Module*> IRModules;
    const LgsAppFile* appFile = nullptr;

    explicit LgsApp() : lgsCLang(paths) {}
    void initPaths(const path& rootDirPath);
    bool validate();
    bool parse();
    bool analyse();
    bool generate();
    bool link() const;
    void run() const;
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(path fileEntry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool generateObjFile(Module* module) const;
    bool resolveExternalFiles();
    bool resolveGlobalTypes() const;
    void setEnvVars();
    void setupActiveEnv();
    void loadGlobals();
    void loadEnvFiles();
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkRequiredEnvVars();
    bool isLogosFile(const directory_entry& entry) const;
    void addErrors(vector<LgsError> newErrors);
    ~LgsApp() = default;
};
