#ifndef LOGOSMAINFILE_H
#define LOGOSMAINFILE_H
#include "LogosDefinitions.h"
#include "LogosFile.h"
#include "funcs/LogosFunc.h"
#include "funcs/LogosUserFunc.h"

class LogosFunc;
class LogosUserFunc;

class LogosMainFile final : public LogosFile {
public:
    LogosUserFunc* mainFunc = nullptr;
    vector<LogosUserFunc*> funcs;

    explicit LogosMainFile(const string& path) : LogosFile(LOGOS_MAIN_FILE, path) {}
    ~LogosMainFile() override;
};


#endif //LOGOSMAINFILE_H
