#ifndef LGSPROJECT_H
#define LGSPROJECT_H
#include "LgsActiveEnv.h"
#include "LgsProjectAnalyser.h"
#include "analysis/LgsAnalyser.h"
#include "files/LgsAppFile.h"
#include "files/LgsEnvFile.h"
#include <files/LgsFile.h>
#include <vector>

class ThreadPool;
class LgsActiveEnv;
class LgsAppFile;
class LgsMainFile;
struct LgsPaths;
class LgsEnv;

class LgsProject final {
public:
    string name;
    string version;
    vector<LgsFile*> files;
    vector<LgsEnvFile*> envFiles;
    LgsProjectAnalyser projectAnalyser;
    const LgsMainFile* mainFile = nullptr;
    const LgsAppFile* appFile = nullptr;
    vector<LgsError> errors;
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
    string getFileText(path filePath) const;
    bool isLogosFile(const directory_entry& entry) const;
    ~LgsProject() = default;
};

#endif // LGSPROJECT_H
