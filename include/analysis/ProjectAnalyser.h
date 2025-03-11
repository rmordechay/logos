#ifndef PROJECTANALYSER_H
#define PROJECTANALYSER_H
#include "LogosAnalyser.h"
#include "LogosError.h"

#include <LogosFile.h>
#include <mutex>
#include <vector>

class ProjectAnalyser final : public LogosAnalyser {
public:
    std::mutex mtx;
    const vector<LogosFile*>& files;

    explicit ProjectAnalyser(const vector<LogosFile*>& files) : files(files) {}
    bool analyse();
    void analyseStructure();
    void printDuplicateFiles(const map<string, vector<LogosFile*>>& duplicates);
};

#endif //PROJECTANALYSER_H
