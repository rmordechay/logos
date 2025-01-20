#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LogosPackage.h"


class SemaAnalyser {
public:
    bool analyseCode(LogosPackage* rootPackage);
    ~SemaAnalyser() = default;
};



#endif //SEMAANALYSER_H
