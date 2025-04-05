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

class LgsProject final : public LgsAnalyser {
public:
    std::mutex mtx;
    LgsPaths* paths;
    const vector<LgsFile*> files;
    const vector<LgsEnv*> envFiles;

    explicit LgsProject(LgsPaths* paths) : paths(paths) {}
    bool validateProject() const;
    void checkDuplicateFiles() const;
    ~LgsProject() = default;
};

#endif //PROJECTANALYSER_H
