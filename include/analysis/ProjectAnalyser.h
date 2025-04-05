#ifndef PROJECTANALYSER_H
#define PROJECTANALYSER_H
#include "LgsAnalyser.h"
#include "../logos/LgsErrors.h"

#include <LgsFile.h>
#include <LgsData.h>
#include <mutex>
#include <vector>

struct LgsPaths;
class LgsEnv;

class ProjectAnalyser final : public LgsAnalyser {
public:
    std::mutex mtx;
    LgsPaths* paths;
    const vector<LgsFile*> files;
    const vector<LgsEnv*> envFiles;

    explicit ProjectAnalyser(LgsPaths* paths) : paths(paths) {}
    bool analyseStructure() const;
    void checkDuplicateFiles() const;
    ~ProjectAnalyser() = default;
};

#endif //PROJECTANALYSER_H
