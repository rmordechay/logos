#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H
#include "LogosRootPackage.h"


class SemaAnalyser {
public:
    bool analyseCode(LogosRootPackage* rootPackage);
    ~SemaAnalyser() = default;
};



#endif //SEMAANALYSER_H
