#pragma once
#include "LgsActiveEnv.h"
#include "extern/LgsC.h"
#include "LgsErrHandler.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include <files/LgsFile.h>


struct LgsError;
class LgsObject;
class LgsFuncType;
class ThreadPool;
class LgsActiveEnv;
class LgsAppFile;
class LgsMainFile;
class LgsEnv;
struct LgsPaths;

using namespace filesystem;

class LogosProject final {
public:
    string name;
    string version;
    vector<LgsFile*> files;
    LgsActiveEnv activeEnv;
    vector<LgsError> errors;
    LgsErrHandler errHandler;
    vector<LgsEnvFile*> envFiles;
    map<string, Module*> IRModules;
    const LgsAppFile* appFile = nullptr;

    void asJSON() const;
    bool loadProject();
    void loadFiles();
    void setEnvVars();
    void loadGlobals();
    void loadSrcFiles();
    void loadEnvFiles();
    void setupActiveEnv();
    bool validateProject();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(path entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool resolveGlobalTypes(const vector<LgsFile*>& files) const;
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles(const vector<LgsFile*>& files);
    void checkRequiredEnvVars();
    bool isLogosFile(const directory_entry& entry) const;
    ~LogosProject() = default;
};


