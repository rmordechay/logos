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
    vector<LogosFunc*> funcs;

    explicit LogosMainFile() : LogosFile(LOGOS_MAIN_FILE) {}
    Module* generateModule(IRBuilder<>& builder, LogosStack& theStack) override;
    void initModule(IRBuilder<>& builder, LogosStack& theStack) override;
    ~LogosMainFile() override;
};


#endif //LOGOSMAINFILE_H
