#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "application/LogosPackage.h"


class SemaAnalyser {
public:
    map<string, LogosFile*> files;
    bool analyseCode(LogosPackage* rootPackage);
    void flattenTree(const LogosPackage* pkg);
    ~SemaAnalyser() = default;
};



#endif //SEMAANALYSER_H
