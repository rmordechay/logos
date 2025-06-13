#pragma once
#include "LgsActiveEnv.h"
#include "LgsErrHandler.h"
#include "Platform.h"

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

class LgsApp final {
public:
    string name;
    string version;
    LgsPaths paths;
    vector<char*> args;
    LgsActiveEnv activeEnv;
    vector<LgsFile*> files;
    LgsErrHandler errHandler;
    vector<LgsEnvFile*> envFiles;
    map<string, Module*> IRModules;
    const LgsAppFile* appFile = nullptr;

    void initPaths(const path& rootDirPath);
    bool validate();
    bool parse();
    bool analyse();
    bool generate();
    bool link() const;
    void run() const;
    void setEnvVars();
    void loadGlobals();
    void loadEnvFiles();
    void setupActiveEnv();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(path entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool generateObjFile(Module* module) const;
    bool resolveGlobalTypes() const;
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles(const vector<LgsFile*>& files);
    void checkRequiredEnvVars();
    bool isLogosFile(const directory_entry& entry) const;
    void addErrors(vector<LgsError> newErrors);
    ~LgsApp() = default;
};
