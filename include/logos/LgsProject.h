#ifndef LGSPROJECT_H
#define LGSPROJECT_H
#include "analysis/AntlrConverter.h"
#include "extern/LgsC.h"
#include "LgsErrHandler.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include <files/LgsFile.h>
#include <vector>

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
    vector<LgsError> errors;
    LgsErrHandler errHandler;
    vector<LgsEnvFile*> envFiles;
    LgsMainFile* mainFile = nullptr;
    const LgsAppFile* appFile = nullptr;
    LgsC lgsC;

    void asJSON() const;
    bool loadProject(const vector<char*>& args);
    void loadFiles();
    void setEnvVars() const;
    void loadGlobals();
    void checkRequiredEnvVars();
    void loadSrcFiles();
    void loadEnvFiles();
    void setupActiveEnv();
    bool validateProject();
    bool resolveGlobalTypes(const vector<LgsFile*>& files) const;
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(path entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles(const vector<LgsFile*>& files);
    bool isLogosFile(const directory_entry& entry) const;
    ~LogosProject() = default;
};

#endif // LGSPROJECT_H
