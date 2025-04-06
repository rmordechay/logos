#ifndef PROJECTANALYSER_H
#define PROJECTANALYSER_H
#include "LgsAnalyser.h"
#include "LgsAppFile.h"
#include "LgsEnvFile.h"
#include "ThreadPool.h"
#include "../logos/LgsErrors.h"

#include <LgsFile.h>
#include <LgsData.h>
#include <mutex>
#include <vector>

class LgsEnv;
class LgsAppFile;
class LgsMainFile;
struct LgsPaths;
class LgsEnvObject;

class LgsProject final : public LgsAnalyser {
public:
    string name;
    string version;
    string activeEnv;
    LgsPaths* paths;
    vector<LgsFile*> files;
    vector<LgsEnvFile*> envFiles;
    const LgsMainFile* mainFile = nullptr;
    const LgsAppFile* appFile = nullptr;
    std::mutex mtx;

    explicit LgsProject(LgsPaths* paths) : paths(paths) {}
    bool loadProject();
    void loadFiles();
    void loadGlobals() const;
    void checkRequiredEnvVars();
    void loadSrcFiles();
    void loadEnvFiles();
    void setupAppEnv();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(const directory_entry& entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool validateProject() const;
    void checkEnvs();
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles() const;
    string getFileText(path filePath) const;
    bool isLogosFile(const directory_entry& entry) const;
    ~LgsProject() = default;
};

#endif //PROJECTANALYSER_H
