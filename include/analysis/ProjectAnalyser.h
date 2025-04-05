#ifndef PROJECTANALYSER_H
#define PROJECTANALYSER_H
#include "LgsAnalyser.h"
#include "../logos/LgsErrors.h"

#include <LgsFile.h>
#include <LgsData.h>
#include <mutex>
#include <vector>

class ProjectAnalyser final : public LgsAnalyser {
public:
    std::mutex mtx;
    const vector<LgsFile*>& files;
    const vector<LgsFile*>& envFiles;

    ProjectAnalyser(const vector<LgsFile*>& files, const vector<LgsFile*>& envFiles)
        : files(files), envFiles(envFiles) {}

    bool analyse() const;
    void analyseEnvs() const;
    void analyseStructure() const;
    void printDuplicateFiles(const map<string, vector<LgsFile*>>& duplicates) const;
};

#endif //PROJECTANALYSER_H
