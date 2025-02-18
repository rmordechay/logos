#ifndef SEMAANALYSER_H
#define SEMAANALYSER_H

#include "LogosStack.h"
#include "SemaFileAnalyser.h"

#include "exprs/LogosUnaryExpr.h"
#include "files/LogosMainFile.h"
#include "files/LogosObjectFile.h"
#include "object/LogosObject.h"

class LogosLoop;

class SemaAnalyser {
public:
    bool successful = true;
    map<string, LogosFile*> files;
    LogosStack mainStack;
    mutex mtx;

    bool analyse();
    void collectGlobals();
    static void visitLogosFile(LogosFile* file, SemaFileAnalyser& semFile);
    ~SemaAnalyser();
};

#endif //SEMAANALYSER_H
