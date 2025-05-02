#ifndef LGSPROJECT_H
#define LGSPROJECT_H
#include "LgsActiveEnv.h"
#include "LgsErrorHandler.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"

#include <files/LgsFile.h>
#include <vector>

class LgsObject;
class LgsFuncSignature;
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
    vector<LgsEnvFile*> envFiles;
    LgsErrorHandler errHandler;
    LgsMainFile* mainFile = nullptr;
    const LgsAppFile* appFile = nullptr;

    void asJSON() const;
    bool loadProject();
    void loadFiles();
    void setEnvVars() const;
    void loadGlobals();
    void checkRequiredEnvVars();
    void loadSrcFiles();
    void loadEnvFiles();
    void setupActiveEnv();
    bool validateProject();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(path entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    string getFileText(path filePath) const;
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles(const vector<LgsFile*>& files);
    void resolveFuncTypes(LgsFuncSignature* signature);
    void resolveGlobalTypes(const vector<LgsFile*>& files);
    void resolveObjMemberTypes(LgsObject* const& obj);
    bool isLogosFile(const directory_entry& entry) const;
    ~LogosProject() = default;
};

#endif // LGSPROJECT_H
