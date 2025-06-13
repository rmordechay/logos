#pragma once
#include "LgsActiveEnv.h"
#include "LgsErrHandler.h"
#include "codegen/LgsLinker.h"

class LgsFile;
class LgsEnvFile;
class LgsObject;
class LgsFuncType;
class ThreadPool;
class LgsActiveEnv;
class LgsAppFile;
class LgsMainFile;
class LgsEnv;
struct LgsError;
struct LgsPaths;
struct RequireEnvVar;

using namespace filesystem;

class LgsProject final {
public:
    string name;
    string version;
    vector<LgsFile*> files;
    LgsActiveEnv activeEnv;
    LgsErrHandler errHandler;
    vector<LgsEnvFile*> envFiles;
    map<string, Module*> IRModules;
    const LgsLinker linker;
    const LgsAppFile* appFile = nullptr;

    void asJSON() const;
    bool parseFiles();
    void setEnvVars();
    void reprocessFuncs() const;
    void loadGlobals();
    void loadEnvFiles();
    void setupActiveEnv();
    bool validateProject();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(path entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool analyse();
    bool generate();
    bool link() const;
    bool resolveGlobalTypes() const;
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles(const vector<LgsFile*>& files);
    void checkRequiredEnvVars();
    bool isLogosFile(const directory_entry& entry) const;
    void addErrors(vector<LgsError> newErrors);
    ~LgsProject() = default;
};


