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

class LgsMainFile;
struct LgsPaths;
class LgsEnv;

class LgsProject final : public LgsAnalyser {
public:
    std::mutex mtx;
    LgsPaths* paths;
    const LgsMainFile* mainFile = nullptr;
    vector<LgsFile*> files;
    vector<LgsEnvFile*> envFiles;

    explicit LgsProject(LgsPaths* paths) : paths(paths) {}
    void loadFiles();
    bool loadProject();
    bool validateProject() const;
    void loadGlobals() const;
    void checkDuplicateFiles() const;
    void loadSrcFiles();
    void parseSrcFiles(const string& path, ThreadPool& threadPool);
    void parseSrcFile(const directory_entry& entry);
    bool isLogosFile(const directory_entry& entry) const;
    string getFileText(path filePath) const;
    void loadEnvFiles();
    void parseEnvFile(path fileEntry);
    ~LgsProject() = default;
};

#endif //PROJECTANALYSER_H
