#ifndef PROJECTANALYSER_H
#define PROJECTANALYSER_H
#include "LgsActiveEnv.h"
#include "LgsAnalyser.h"
#include "LgsAppFile.h"
#include "LgsEnvFile.h"
#include "ThreadPool.h"
#include <LgsFile.h>
#include <vector>

class LgsActiveEnv;
class LgsAppFile;
class LgsMainFile;
struct LgsPaths;
class LgsEnv;

class LgsProject final : public LgsAnalyser {
public:
    string name;
    string version;
    vector<LgsFile*> files;
    vector<LgsEnvFile*> envFiles;
    const LgsMainFile* mainFile = nullptr;
    const LgsAppFile* appFile = nullptr;
    std::mutex mtx;

    bool loadProject();
    void loadFiles();
    void setEnvVars() const;
    void loadGlobals() const;
    void checkRequiredEnvVars();
    void loadSrcFiles();
    void loadEnvFiles();
    void setupActiveEnv();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(const directory_entry& entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool validateProject() const;
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles() const;
    string getFileText(path filePath) const;
    bool isLogosFile(const directory_entry& entry) const;
    ~LgsProject() = default;
};

#endif //PROJECTANALYSER_H
