#ifndef PROJECTANALYSER_H
#define PROJECTANALYSER_H
#include "LgsAnalyser.h"
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
    std::mutex mtx;
    LgsPaths* paths;
    vector<LgsFile*> files;
    const LgsMainFile* mainFile = nullptr;
    const LgsAppFile* appFile = nullptr;
    const LgsEnvFile* activeEnv = nullptr;

    explicit LgsProject(LgsPaths* paths) : paths(paths) {}
    bool loadProject();
    void loadFiles();
    void loadGlobals() const;
    void loadSrcFiles();
    void setAppEnv();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(const directory_entry& entry);
    void parseEnvFile(path fileEntry);
    void parseAppFile(path fileEntry);
    bool validateProject() const;
    void checkEnvs() const;
    void checkDuplicateFiles() const;
    string getFileText(path filePath) const;
    bool isLogosFile(const directory_entry& entry) const;
    ~LgsProject() = default;
};

#endif //PROJECTANALYSER_H
