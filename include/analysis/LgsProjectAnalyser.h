#ifndef PROJECTANALYSER_H
#define PROJECTANALYSER_H
#include "LgsAnalyser.h"

class LgsEnvFile;
struct RequireEnvVar;

class LgsProjectAnalyser final : public LgsAnalyser {
public:
    bool validateProject();
    void checkRequiredEnvVar(const RequireEnvVar& requireEnvVar, LgsEnvFile* envFile);
    void checkDuplicateFiles(const vector<LgsFile*>& files);
    ~LgsProjectAnalyser() = default;
};

#endif //PROJECTANALYSER_H
