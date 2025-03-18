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

    explicit ProjectAnalyser(const vector<LgsFile*>& files) : files(files) {}
    bool analyse();
    void analyseStructure();
    void printDuplicateFiles(const map<string, vector<LgsFile*>>& duplicates);
};

#endif //PROJECTANALYSER_H
